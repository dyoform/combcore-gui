package main

import (
	"os"

	"github.com/therecipe/qt/core"
	"github.com/therecipe/qt/uitools"
	"github.com/therecipe/qt/widgets"
)

type qtGUI struct {
	app      *widgets.QApplication
	window   *widgets.QMainWindow
	stack    *widgets.QStackedWidget
	overview *widgets.QWidget
	action   *widgets.QWidget
	wallet   *widgets.QWidget
	status   *widgets.QLabel

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
}

var root qtGUI

func set_style() {
	root.app.SetStyle(widgets.QStyleFactory_Create("fusion"))
	root.app.SetStyleSheet("QToolButton { margin-bottom: 6px; }")
}

func load_widget(path string) *widgets.QWidget {
	file := core.NewQFile2(":qml/" + path + ".ui")
	file.Open(core.QIODevice__ReadOnly)
	out := uitools.NewQUiLoader(nil).Load(file, nil)
	file.Close()
	return out
}

func bind_actions() {
	root.tabOverview = widgets.NewQActionFromPointer(root.window.FindChild("actionOverview", core.Qt__FindChildrenRecursively).Pointer())
	root.tabAction = widgets.NewQActionFromPointer(root.window.FindChild("actionAction", core.Qt__FindChildrenRecursively).Pointer())
	root.tabWallet = widgets.NewQActionFromPointer(root.window.FindChild("actionWallet", core.Qt__FindChildrenRecursively).Pointer())

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

func load_gui() {
	root.app = widgets.NewQApplication(len(os.Args), os.Args)

	set_style()

	root.window = widgets.NewQMainWindowFromPointer(load_widget("main").Pointer())
	root.stack = widgets.NewQStackedWidgetFromPointer(root.window.FindChild("mainStack", core.Qt__FindChildrenRecursively).Pointer())

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
}

func main() {
	root = qtGUI{}

	load_gui()
	bind_actions()

	root.window.Show()
	root.app.Exec()
}
