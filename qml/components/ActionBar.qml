import QtQuick 2.15
import QtQuick.Controls 2.12
import combcore 1.0
import combcore.gui 1.0

import "../"

Rectangle {
    width: 50
    color: Constants.structureColor
    Column {
        id: actionColumn
        anchors.fill: parent

        ActionButton {
            guiAction: ActionControls.ACTION_OVERVIEW
            icon.source: "qrc:/images/overview.svg"
        }
        ActionButton {
            guiAction: ActionControls.ACTION_WALLET
            icon.source: "qrc:/images/wallet.svg"
        }
        ActionButton {
            guiAction: ActionControls.ACTION_ACTIONS
            icon.source: "qrc:/images/actions.svg"
        }
        Item {
            width: 50
            height: parent.height - 200
        }
        ActionButton {

            guiAction: ActionControls.ACTION_SETTINGS
            icon.source: "qrc:/images/settings.svg"
        }

        ButtonGroup {
            buttons: actionColumn.children
        }
    }
}
