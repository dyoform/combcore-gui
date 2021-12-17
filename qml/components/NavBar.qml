import QtQuick 2.15
import QtQuick.Controls 2.12
import combcore 1.0
import combcore.gui 1.0

import "../"

Rectangle {
    property ScreenControls controls: GUI.screenControls
    width: 50
    color: Constants.structureColor
    Column {
        id: navColumn
        anchors.fill: parent

        NavButton {
            guiScreen: ScreenControls.SCREEN_OVERVIEW
            icon.source: "qrc:/images/overview.svg"
        }
        NavButton {
            guiScreen: ScreenControls.SCREEN_WALLET
            icon.source: "qrc:/images/wallet.svg"
        }
        NavButton {
            guiScreen: ScreenControls.SCREEN_ACTIONS
            icon.source: "qrc:/images/actions.svg"
        }
        Item {
            width: 50
            height: parent.height - 200
        }
        NavButton {

            guiScreen: ScreenControls.SCREEN_SETTINGS
            icon.source: "qrc:/images/settings.svg"
        }

        ButtonGroup {
            buttons: navColumn.children
        }
    }
}
