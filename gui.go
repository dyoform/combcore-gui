package main

import (
	"fmt"
	"os"

	"github.com/therecipe/qt/core"
	"github.com/therecipe/qt/gui"
	"github.com/therecipe/qt/uitools"
	"github.com/therecipe/qt/widgets"
)

const (
	KEYS         = 1
	TRANSACTIONS = 2
	STACKS       = 4
	CONTRACTS    = 8
	DECIDERS     = 16
)

type qtGUI struct {
	app       *widgets.QApplication
	window    *widgets.QMainWindow
	stack     *widgets.QStackedWidget
	overview  *widgets.QWidget
	action    *widgets.QWidget
	wallet    *widgets.QWidget
	status    *widgets.QLabel
	monospace *gui.QFont

	actionModes *widgets.QStackedWidget
	actionCombo *widgets.QComboBox
	key         *widgets.QWidget
	claim       *widgets.QWidget
	transaction *widgets.QWidget
	liquidity   *widgets.QWidget
	contract    *widgets.QWidget
	decider     *widgets.QWidget

	tabGroup    *widgets.QActionGroup
	tabOverview *widgets.QAction
	tabAction   *widgets.QAction
	tabWallet   *widgets.QAction

	selectDialog *widgets.QDialog
	selectOutput *widgets.QLineEdit
	selectTabs   *widgets.QTabWidget

	keyView      *widgets.QListView
	txView       *widgets.QListView
	stackView    *widgets.QListView
	contractView *widgets.QListView
	deciderView  *widgets.QListView
}

var root qtGUI

func show_dialog(visible int, output *widgets.QLineEdit) {
	root.selectOutput = output
	for root.selectTabs.Count() != 0 {
		root.selectTabs.RemoveTab(0)
	}
	if visible&KEYS != 0 {
		view := widgets.NewQListView(nil)
		view.SetFont(root.monospace)
		view.SetModel(keyModel)
		root.selectTabs.AddTab(view, "Keys")
	}
	if visible&STACKS != 0 {
		view := widgets.NewQListView(nil)
		view.SetFont(root.monospace)
		view.SetModel(stackModel)
		root.selectTabs.AddTab(view, "Stacks")
	}
	if visible&TRANSACTIONS != 0 {
		view := widgets.NewQListView(nil)
		view.SetFont(root.monospace)
		view.SetModel(txModel)
		root.selectTabs.AddTab(view, "Transactions")
	}
	if visible&TRANSACTIONS != 0 {
		view := widgets.NewQListView(nil)
		view.SetFont(root.monospace)
		root.selectTabs.AddTab(view, "Contracts")
	}
	if visible&DECIDERS != 0 {
		view := widgets.NewQListView(nil)
		view.SetFont(root.monospace)
		view.SetModel(deciderModel)
		root.selectTabs.AddTab(view, "Deciders")
	}
	root.selectDialog.Show()
}

func return_dialog() string {
	list := widgets.NewQListViewFromPointer(root.selectTabs.CurrentWidget().Pointer())
	return list.CurrentIndex().Data(0).ToString()
}

func load_icon(name string) *gui.QIcon {
	image := gui.NewQImage9(":qml/icons/"+name+".png", "PNG")
	color := gui.NewQPalette().Color2(gui.QPalette__Text)
	if color.LightnessF() > 0.5 {
		image.InvertPixels(gui.QImage__InvertRgb)
	}
	pixmap := gui.NewQPixmap()
	pixmap.ConvertFromImage(image, 0)
	icon := gui.NewQIcon2(pixmap)

	return icon
}

func set_style() {
	root.app.SetStyle(widgets.QStyleFactory_Create("fusion"))
	var fontfile = core.NewQFile2(":qml/fonts/Cantarell-Regular.ttf")
	var family string
	if fontfile.Open(core.QIODevice__ReadOnly) {
		fontdata := fontfile.ReadAll()
		fntdb := gui.NewQFontDatabase()
		fntid := fntdb.AddApplicationFontFromData(fontdata)
		family = fntdb.ApplicationFontFamilies(fntid)[0]
		main := gui.NewQFont2(family, 11, 50, false)
		root.app.SetFont(main, "")
	}

	fontfile = core.NewQFile2(":qml/fonts/SourceCodePro-Regular.ttf")
	if fontfile.Open(core.QIODevice__ReadOnly) {
		fontdata := fontfile.ReadAll()
		fntdb := gui.NewQFontDatabase()
		fntid := fntdb.AddApplicationFontFromData(fontdata)
		family = fntdb.ApplicationFontFamilies(fntid)[0]
		root.app.SetFont(gui.NewQFont2(family, 11, 50, false), "QLineEdit")
		root.monospace = gui.NewQFont2(family, 11, 50, false)
	}
}

func load_widget(path string) *widgets.QWidget {
	file := core.NewQFile2(":qml/" + path + ".ui")
	file.Open(core.QIODevice__ReadOnly)
	out := uitools.NewQUiLoader(nil).Load(file, nil)
	file.Close()
	return out
}

func bind_actions() {
	root.tabOverview.SetIcon(load_icon("overview"))
	root.tabAction.SetIcon(load_icon("edit"))
	root.tabWallet.SetIcon(load_icon("history"))

	root.tabGroup.AddAction(root.tabOverview)
	root.tabGroup.AddAction(root.tabAction)
	root.tabGroup.AddAction(root.tabWallet)

	root.tabOverview.ConnectToggled(func(vbo bool) {
		if vbo {
			root.stack.SetCurrentIndex(0)
		}
	})

	root.tabAction.ConnectToggled(func(vbo bool) {
		if vbo {
			root.stack.SetCurrentIndex(1)
		}
	})

	root.tabWallet.ConnectToggled(func(vbo bool) {
		if vbo {
			root.stack.SetCurrentIndex(2)
		}
	})

	root.actionCombo.ConnectCurrentIndexChanged(func(index int) {
		root.actionModes.SetCurrentIndex(index)
	})
}

func bind_import() {
	//keypair
	{
		labelEdit := widgets.NewQLineEditFromPointer(root.key.FindChild("labelEdit", core.Qt__FindChildrenRecursively).Pointer())
		keyCreate := *widgets.NewQPushButtonFromPointer(root.key.FindChild("createButton", core.Qt__FindChildrenRecursively).Pointer())
		keyCreate.ConnectClicked(func(_ bool) {
			create_keypair(labelEdit.Text())
		})
	}
	//claim
	{
		addressEdit := widgets.NewQLineEditFromPointer(root.claim.FindChild("addressEdit", core.Qt__FindChildrenRecursively).Pointer())
		addressImport := widgets.NewQToolButtonFromPointer(root.claim.FindChild("addressImportButton", core.Qt__FindChildrenRecursively).Pointer())
		feeBox := widgets.NewQSpinBoxFromPointer(root.claim.FindChild("feeBox", core.Qt__FindChildrenRecursively).Pointer())
		qtyBox := widgets.NewQSpinBoxFromPointer(root.claim.FindChild("qtyBox", core.Qt__FindChildrenRecursively).Pointer())
		claimButton := widgets.NewQPushButtonFromPointer(root.claim.FindChild("claimButton", core.Qt__FindChildrenRecursively).Pointer())

		addressImport.ConnectClicked(func(_ bool) {
			show_dialog(KEYS|STACKS, addressEdit)
		})

		claimButton.ConnectClicked(func(_ bool) {
			make_claim(addressEdit.Text(), uint16(feeBox.Value()), uint16(qtyBox.Value()))
		})
	}
	//tx
	{
		destinationEdit := widgets.NewQLineEditFromPointer(root.transaction.FindChild("destinationEdit", core.Qt__FindChildrenRecursively).Pointer())
		destinationImport := widgets.NewQToolButtonFromPointer(root.transaction.FindChild("destinationImportButton", core.Qt__FindChildrenRecursively).Pointer())
		sourceCombo := widgets.NewQComboBoxFromPointer(root.transaction.FindChild("sourceCombo", core.Qt__FindChildrenRecursively).Pointer())
		confirmButton := widgets.NewQPushButtonFromPointer(root.transaction.FindChild("confirmButton", core.Qt__FindChildrenRecursively).Pointer())

		sourceCombo.SetModel(keyModel)

		destinationImport.ConnectClicked(func(_ bool) {
			show_dialog(KEYS|STACKS, destinationEdit)
		})

		confirmButton.ConnectClicked(func(_ bool) {
			make_transaction(sourceCombo.CurrentText(), destinationEdit.Text())
		})

	}
	//stack
	{
		destinationEdit := widgets.NewQLineEditFromPointer(root.liquidity.FindChild("destinationEdit", core.Qt__FindChildrenRecursively).Pointer())
		destinationImport := widgets.NewQToolButtonFromPointer(root.liquidity.FindChild("destinationImportButton", core.Qt__FindChildrenRecursively).Pointer())
		changeEdit := widgets.NewQLineEditFromPointer(root.liquidity.FindChild("changeEdit", core.Qt__FindChildrenRecursively).Pointer())
		changeImport := widgets.NewQToolButtonFromPointer(root.liquidity.FindChild("changeImportButton", core.Qt__FindChildrenRecursively).Pointer())
		combEdit := widgets.NewQDoubleSpinBoxFromPointer(root.liquidity.FindChild("combEdit", core.Qt__FindChildrenRecursively).Pointer())
		natsEdit := widgets.NewQSpinBoxFromPointer(root.liquidity.FindChild("natsEdit", core.Qt__FindChildrenRecursively).Pointer())
		spinStack := widgets.NewQStackedWidgetFromPointer(root.liquidity.FindChild("spinStack", core.Qt__FindChildrenRecursively).Pointer())
		unitsCombo := widgets.NewQComboBoxFromPointer(root.liquidity.FindChild("unitsCombo", core.Qt__FindChildrenRecursively).Pointer())
		labelEdit := widgets.NewQLineEditFromPointer(root.liquidity.FindChild("labelEdit", core.Qt__FindChildrenRecursively).Pointer())
		createButton := widgets.NewQPushButtonFromPointer(root.liquidity.FindChild("createButton", core.Qt__FindChildrenRecursively).Pointer())

		destinationImport.ConnectClicked(func(_ bool) {
			show_dialog(KEYS|STACKS, destinationEdit)
		})

		//conversion has fp errors, this needs to be replaced
		unitsCombo.ConnectCurrentIndexChanged(func(index int) {
			spinStack.SetCurrentIndex(index)
			if index == 0 {
				value := float64(natsEdit.Value())
				combEdit.SetValue(value / 100000000.0)
			} else {
				value := combEdit.Value()
				natsEdit.SetValue(int(value * 100000000))
			}
		})

		changeImport.ConnectClicked(func(_ bool) {
			show_dialog(KEYS|STACKS, changeEdit)
		})

		createButton.ConnectClicked(func(_ bool) {
			var nats uint64
			if unitsCombo.CurrentIndex() == 0 {
				nats = uint64(combEdit.Value()) * 100000000
			} else {
				nats = uint64(natsEdit.Value())
			}
			create_stack(labelEdit.Text(), destinationEdit.Text(), changeEdit.Text(), nats)
		})

	}
	//contract
	{
		shortDeciderEdit := widgets.NewQLineEditFromPointer(root.contract.FindChild("shortDeciderEdit", core.Qt__FindChildrenRecursively).Pointer())
		shortDeciderImport := widgets.NewQToolButtonFromPointer(root.contract.FindChild("shortDeciderImportButton", core.Qt__FindChildrenRecursively).Pointer())
		forwardEdit := widgets.NewQLineEditFromPointer(root.contract.FindChild("forwardEdit", core.Qt__FindChildrenRecursively).Pointer())
		forwardImport := widgets.NewQToolButtonFromPointer(root.contract.FindChild("forwardImportButton", core.Qt__FindChildrenRecursively).Pointer())
		rollbackEdit := widgets.NewQLineEditFromPointer(root.contract.FindChild("rollbackEdit", core.Qt__FindChildrenRecursively).Pointer())
		rollbackImport := widgets.NewQToolButtonFromPointer(root.contract.FindChild("rollbackImportButton", core.Qt__FindChildrenRecursively).Pointer())
		longDeciderEdit := widgets.NewQLineEditFromPointer(root.contract.FindChild("longDeciderEdit", core.Qt__FindChildrenRecursively).Pointer())
		longDeciderImport := widgets.NewQToolButtonFromPointer(root.contract.FindChild("longDeciderImportButton", core.Qt__FindChildrenRecursively).Pointer())
		contractCombo := *widgets.NewQComboBoxFromPointer(root.contract.FindChild("contractCombo", core.Qt__FindChildrenRecursively).Pointer())
		labelEdit := widgets.NewQLineEditFromPointer(root.contract.FindChild("labelEdit", core.Qt__FindChildrenRecursively).Pointer())
		maskBox := widgets.NewQSpinBoxFromPointer(root.contract.FindChild("maskBox", core.Qt__FindChildrenRecursively).Pointer())
		createButton := widgets.NewQPushButtonFromPointer(root.contract.FindChild("createButton", core.Qt__FindChildrenRecursively).Pointer())
		redeemButton := widgets.NewQPushButtonFromPointer(root.contract.FindChild("redeemButton", core.Qt__FindChildrenRecursively).Pointer())

		shortDeciderImport.ConnectClicked(func(_ bool) {
			show_dialog(DECIDERS, shortDeciderEdit)
		})

		forwardImport.ConnectClicked(func(_ bool) {
			show_dialog(KEYS|STACKS, forwardEdit)
		})

		rollbackImport.ConnectClicked(func(_ bool) {
			show_dialog(KEYS|STACKS, rollbackEdit)
		})

		longDeciderImport.ConnectClicked(func(_ bool) {
			show_dialog(DECIDERS, longDeciderEdit)
		})

		createButton.ConnectClicked(func(_ bool) {
			create_contract(labelEdit.Text(), forwardEdit.Text(), rollbackEdit.Text(), shortDeciderEdit.Text(), uint16(maskBox.Value()))
		})

		redeemButton.ConnectClicked(func(_ bool) {
			redeem_contract(contractCombo.CurrentText(), longDeciderEdit.Text())
		})

	}
	//decider
	{
		aEdit := *widgets.NewQLineEditFromPointer(root.decider.FindChild("aEdit", core.Qt__FindChildrenRecursively).Pointer())
		bEdit := *widgets.NewQLineEditFromPointer(root.decider.FindChild("bEdit", core.Qt__FindChildrenRecursively).Pointer())
		labelEdit := *widgets.NewQLineEditFromPointer(root.decider.FindChild("labelEdit", core.Qt__FindChildrenRecursively).Pointer())
		createButton := *widgets.NewQPushButtonFromPointer(root.decider.FindChild("createButton", core.Qt__FindChildrenRecursively).Pointer())

		deciderCombo := *widgets.NewQComboBoxFromPointer(root.decider.FindChild("deciderCombo", core.Qt__FindChildrenRecursively).Pointer())
		signBox := *widgets.NewQSpinBoxFromPointer(root.decider.FindChild("signBox", core.Qt__FindChildrenRecursively).Pointer())
		decideButton := *widgets.NewQPushButtonFromPointer(root.decider.FindChild("decideButton", core.Qt__FindChildrenRecursively).Pointer())

		generateButton := *widgets.NewQPushButtonFromPointer(root.decider.FindChild("generateButton", core.Qt__FindChildrenRecursively).Pointer())

		createButton.ConnectClicked(func(_ bool) {
			create_decider(labelEdit.Text(), aEdit.Text(), bEdit.Text())
		})

		generateButton.ConnectClicked(func(_ bool) {
			aEdit.SetText(randhex32())
			bEdit.SetText(randhex32())
		})

		decideButton.ConnectClicked(func(_ bool) {
			decide_decider(deciderCombo.CurrentText(), uint16(signBox.Value()))
		})
	}
}

func bind_select() {
	root.selectDialog.SetModal(true)
	root.selectDialog.ConnectAccepted(func() {
		root.selectOutput.SetText(return_dialog())
	})

	importRe := core.NewQRegularExpression2("importbutton", core.QRegularExpression__CaseInsensitiveOption)
	if !importRe.IsValid() {
		fmt.Println(importRe.ErrorString())
	} else {
		importButtons := root.action.FindChildren3(importRe, core.Qt__FindChildrenRecursively)
		importIcon := load_icon("import")
		for _, b := range importButtons {
			button := widgets.NewQToolButtonFromPointer(b.Pointer())
			button.SetIcon(importIcon)
		}
	}
}

func load_gui() {
	root.app = widgets.NewQApplication(len(os.Args), os.Args)

	set_style()

	root.window = widgets.NewQMainWindowFromPointer(load_widget("main").Pointer())
	toolbar := widgets.NewQToolBarFromPointer(root.window.FindChild("toolBar", core.Qt__FindChildrenRecursively).Pointer())
	toolbar.SetStyleSheet("QToolButton { margin-bottom: 6px; }")
	root.stack = widgets.NewQStackedWidgetFromPointer(root.window.FindChild("mainStack", core.Qt__FindChildrenRecursively).Pointer())
	root.tabOverview = widgets.NewQActionFromPointer(root.window.FindChild("actionOverview", core.Qt__FindChildrenRecursively).Pointer())
	root.tabAction = widgets.NewQActionFromPointer(root.window.FindChild("actionAction", core.Qt__FindChildrenRecursively).Pointer())
	root.tabWallet = widgets.NewQActionFromPointer(root.window.FindChild("actionWallet", core.Qt__FindChildrenRecursively).Pointer())

	root.overview = load_widget("overview")
	root.wallet = load_widget("wallet")
	root.action = load_widget("action")

	root.actionModes = widgets.NewQStackedWidgetFromPointer(root.action.FindChild("modeStack", core.Qt__FindChildrenRecursively).Pointer())
	root.actionCombo = widgets.NewQComboBoxFromPointer(root.action.FindChild("modeCombo", core.Qt__FindChildrenRecursively).Pointer())

	root.key = load_widget("key")
	root.claim = load_widget("claim")
	root.transaction = load_widget("transaction")
	root.liquidity = load_widget("stack")
	root.contract = load_widget("contract")
	root.decider = load_widget("decider")

	root.keyView = widgets.NewQListViewFromPointer(root.wallet.FindChild("keyView", core.Qt__FindChildrenRecursively).Pointer())
	root.txView = widgets.NewQListViewFromPointer(root.wallet.FindChild("txView", core.Qt__FindChildrenRecursively).Pointer())
	root.stackView = widgets.NewQListViewFromPointer(root.wallet.FindChild("stackView", core.Qt__FindChildrenRecursively).Pointer())
	root.contractView = widgets.NewQListViewFromPointer(root.wallet.FindChild("contractView", core.Qt__FindChildrenRecursively).Pointer())
	root.deciderView = widgets.NewQListViewFromPointer(root.wallet.FindChild("deciderView", core.Qt__FindChildrenRecursively).Pointer())

	root.stack.AddWidget(root.overview)
	root.stack.AddWidget(root.action)
	root.stack.AddWidget(root.wallet)
	root.stack.SetCurrentIndex(0)

	root.actionModes.AddWidget(root.key)
	root.actionModes.AddWidget(root.claim)
	root.actionModes.AddWidget(root.transaction)
	root.actionModes.AddWidget(root.liquidity)
	root.actionModes.AddWidget(root.contract)
	root.actionModes.AddWidget(root.decider)
	root.actionModes.SetCurrentIndex(0)

	root.tabGroup = widgets.NewQActionGroup(root.window)

	root.status = widgets.NewQLabel(root.window.StatusBar(), 0)
	root.status.SetText("Fetching commits...")
	root.window.StatusBar().AddWidget(root.status, 0)

	root.selectDialog = widgets.NewQDialogFromPointer(load_widget("select").Pointer())
	root.selectTabs = widgets.NewQTabWidgetFromPointer(root.selectDialog.FindChild("tabs", core.Qt__FindChildrenRecursively).Pointer())
}

func run_gui() {
	root.window.Show()
	root.app.Exec()
}

func init() {
	root = qtGUI{}
}
