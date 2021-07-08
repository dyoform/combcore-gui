package main

import (
	"fmt"

	"github.com/therecipe/qt/core"
	"github.com/therecipe/qt/widgets"
)

var keyModel *core.QAbstractListModel
var keySelected keypair
var stackModel *core.QAbstractListModel
var stackSelected stack
var txModel *core.QAbstractListModel
var txSelected transaction
var contractModel *core.QAbstractListModel
var contractSelected contract
var deciderModel *core.QAbstractListModel
var deciderSelected decider

func load_models() {
	keyModel = core.NewQAbstractListModel(nil)
	keyModel.ConnectRowCount(func(parent *core.QModelIndex) int {
		return len(get_keys())
	})
	keyModel.ConnectData(func(index *core.QModelIndex, role int) *core.QVariant {
		if role == 0 {
			selected := get_keys()[index.Row()]
			if selected.label != "" {
				return core.NewQVariant1(selected.label)
			} else {
				return core.NewQVariant1(selected.public)
			}
		} else {
			return core.NewQVariant()
		}
	})

	keyView := *widgets.NewQListViewFromPointer(root.wallet.FindChild("keyView", core.Qt__FindChildrenRecursively).Pointer())
	keyView.SetModel(keyModel)

	keyAddress := *widgets.NewQLineEditFromPointer(root.wallet.FindChild("keyAddress", core.Qt__FindChildrenRecursively).Pointer())

	keyView.SelectionModel().ConnectCurrentChanged(func(current, previous *core.QModelIndex) {
		key := get_keys()[current.Row()]
		keyAddress.SetText(key.public)
	})

	stackModel = core.NewQAbstractListModel(nil)
	stackModel.ConnectRowCount(func(parent *core.QModelIndex) int {
		return len(get_stacks())
	})
	stackModel.ConnectData(func(index *core.QModelIndex, role int) *core.QVariant {
		if role == 0 {
			selected := get_stacks()[index.Row()]
			if selected.label != "" {
				return core.NewQVariant1(selected.label)
			} else {
				return core.NewQVariant1(selected.address)
			}
		} else {
			return core.NewQVariant()
		}
	})

	stackView := *widgets.NewQListViewFromPointer(root.wallet.FindChild("stackView", core.Qt__FindChildrenRecursively).Pointer())
	stackView.SetModel(stackModel)

	stackAddress := *widgets.NewQLineEditFromPointer(root.wallet.FindChild("stackAddress", core.Qt__FindChildrenRecursively).Pointer())
	stackChange := *widgets.NewQLineEditFromPointer(root.wallet.FindChild("stackChange", core.Qt__FindChildrenRecursively).Pointer())
	stackDestination := *widgets.NewQLineEditFromPointer(root.wallet.FindChild("stackDestination", core.Qt__FindChildrenRecursively).Pointer())
	stackSum := *widgets.NewQLineEditFromPointer(root.wallet.FindChild("stackSum", core.Qt__FindChildrenRecursively).Pointer())
	stackUnits := *widgets.NewQComboBoxFromPointer(root.wallet.FindChild("stackUnits", core.Qt__FindChildrenRecursively).Pointer())
	stackUnitsUpdate := func(index int) {
		if index == 0 {
			stackSum.SetText(nats_to_comb(stackSelected.sum))
		} else if stackSelected.sum != 0 {
			stackSum.SetText(fmt.Sprint(stackSelected.sum))
		} else {
			stackSum.SetText("0")
		}
	}
	stackView.SelectionModel().ConnectCurrentChanged(func(current, previous *core.QModelIndex) {
		stackSelected = get_stacks()[current.Row()]
		stackAddress.SetText(stackSelected.address)
		stackChange.SetText(stackSelected.change)
		stackDestination.SetText(stackSelected.destination)
		stackUnitsUpdate(stackUnits.CurrentIndex())
	})

	stackUnits.ConnectCurrentIndexChanged(func(index int) {
		stackUnitsUpdate(index)
	})

	txModel = core.NewQAbstractListModel(nil)
	txModel.ConnectRowCount(func(parent *core.QModelIndex) int {
		return len(get_transactions())
	})
	txModel.ConnectData(func(index *core.QModelIndex, role int) *core.QVariant {
		if role == 0 {
			return core.NewQVariant1(get_transactions()[index.Row()].id)
		} else {
			return core.NewQVariant()
		}
	})

	txView := *widgets.NewQListViewFromPointer(root.wallet.FindChild("txView", core.Qt__FindChildrenRecursively).Pointer())
	txView.SetModel(txModel)

	txID := *widgets.NewQLineEditFromPointer(root.wallet.FindChild("txID", core.Qt__FindChildrenRecursively).Pointer())
	txSource := *widgets.NewQLineEditFromPointer(root.wallet.FindChild("txSource", core.Qt__FindChildrenRecursively).Pointer())
	txDestination := *widgets.NewQLineEditFromPointer(root.wallet.FindChild("txDestination", core.Qt__FindChildrenRecursively).Pointer())

	txView.SelectionModel().ConnectCurrentChanged(func(current, previous *core.QModelIndex) {
		index := current.Row()
		if index != -1 {
			txSelected = get_transactions()[index]
			txID.SetText(txSelected.id)
			txSource.SetText(txSelected.source)
			txDestination.SetText(txSelected.destination)
		}
	})

	deciderModel = core.NewQAbstractListModel(nil)
	deciderModel.ConnectRowCount(func(parent *core.QModelIndex) int {
		return len(get_deciders())
	})
	deciderModel.ConnectData(func(index *core.QModelIndex, role int) *core.QVariant {
		if role == 0 {
			selected := get_deciders()[index.Row()]
			if selected.label != "" {
				return core.NewQVariant1(selected.label)
			} else {
				return core.NewQVariant1(selected.short_decider)
			}
		} else {
			return core.NewQVariant()
		}
	})

	deciderView := *widgets.NewQListViewFromPointer(root.wallet.FindChild("deciderView", core.Qt__FindChildrenRecursively).Pointer())
	deciderView.SetModel(deciderModel)

	deciderShort := *widgets.NewQLineEditFromPointer(root.wallet.FindChild("deciderShort", core.Qt__FindChildrenRecursively).Pointer())
	deciderLong := *widgets.NewQLineEditFromPointer(root.wallet.FindChild("deciderLong", core.Qt__FindChildrenRecursively).Pointer())

	deciderView.SelectionModel().ConnectCurrentChanged(func(current, previous *core.QModelIndex) {
		deciderSelected = get_deciders()[current.Row()]
		deciderShort.SetText(deciderSelected.short_decider)
		deciderShort.SetEnabled(deciderSelected.short_decider != "")
		deciderLong.SetText(deciderSelected.long_decider)
		deciderLong.SetEnabled(deciderSelected.long_decider != "")
	})

	deciderCombo := widgets.NewQComboBoxFromPointer(root.decider.FindChild("deciderCombo", core.Qt__FindChildrenRecursively).Pointer())
	deciderCombo.SetModel(deciderModel)

	contractModel = core.NewQAbstractListModel(nil)
	contractModel.ConnectRowCount(func(parent *core.QModelIndex) int {
		return len(get_contracts())
	})
	contractModel.ConnectData(func(index *core.QModelIndex, role int) *core.QVariant {
		if role == 0 {
			selected := get_contracts()[index.Row()]
			if selected.label != "" {
				return core.NewQVariant1(selected.label)
			} else {
				return core.NewQVariant1(selected.address)
			}
		} else {
			return core.NewQVariant()
		}
	})
	contractView := widgets.NewQListViewFromPointer(root.wallet.FindChild("contractView", core.Qt__FindChildrenRecursively).Pointer())
	contractView.SetModel(contractModel)

	contractAddress := *widgets.NewQLineEditFromPointer(root.wallet.FindChild("contractAddress", core.Qt__FindChildrenRecursively).Pointer())
	contractForward := *widgets.NewQLineEditFromPointer(root.wallet.FindChild("contractForward", core.Qt__FindChildrenRecursively).Pointer())
	contractRollback := *widgets.NewQLineEditFromPointer(root.wallet.FindChild("contractRollback", core.Qt__FindChildrenRecursively).Pointer())
	contractDecider := *widgets.NewQLineEditFromPointer(root.wallet.FindChild("contractDecider", core.Qt__FindChildrenRecursively).Pointer())
	contractMask := *widgets.NewQLineEditFromPointer(root.wallet.FindChild("contractMask", core.Qt__FindChildrenRecursively).Pointer())

	contractView.SelectionModel().ConnectCurrentChanged(func(current, previous *core.QModelIndex) {
		contractSelected = get_contracts()[current.Row()]
		contractAddress.SetText(contractSelected.address)
		contractForward.SetText(contractSelected.forward)
		contractRollback.SetText(contractSelected.rollback)
		contractDecider.SetText(contractSelected.short_decider.short_decider)
		contractMask.SetText(fmt.Sprint(contractSelected.mask))
	})

	contractCombo := *widgets.NewQComboBoxFromPointer(root.contract.FindChild("contractCombo", core.Qt__FindChildrenRecursively).Pointer())
	contractCombo.SetModel(contractModel)
}
