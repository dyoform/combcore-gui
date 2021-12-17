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
    width: 980
    height: 540
    visible: true
    color: Constants.backgroundColor
    title: qsTr("COMBCore")

    NavBar {
        id: navBar
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
    }

    StackLayout {
        anchors.margins: 5
        anchors.left: navBar.right
        anchors.top: parent.top
        anchors.bottom: statusBar.top
        anchors.right: parent.right
        currentIndex: GUI.screenControls.activeScreen
        OverviewScreen {
        }
        WalletScreen {
        }
        ActionsScreen {
        }
    }

    Rectangle {
        id: statusBar
        color: Constants.darkStructureColor
        height: 24
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.left: navBar.right
        SText {
            anchors.fill: parent
            topPadding: 3
            leftPadding: 5

            text: GUI.overview.status
            font.bold: true
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
