import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.15
import combcore 1.0
import combcore.gui 1.0

import "style"
import "components"

ApplicationWindow {
    id: window
    width: 960
    height: 540
    visible: true
    color: Constants.backgroundColor
    title: qsTr("COMBCore")

    ActionBar {
        id: actionBar
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
    }

    StackLayout {
        anchors.margins: 5
        anchors.left: actionBar.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        currentIndex: GUI.actionControls.activeAction
        OverviewScreen {
        }
        WalletScreen {
        }
        ActionsScreen {
        }
    }

    menuBar: SettingsBar {

    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.33}D{i:2}D{i:1}D{i:3}
}
##^##*/
