import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.15

import combcore 1.0
import combcore.gui 1.0

import "../style"
import "../"

Item {

    Rectangle {
        id: actionsContainer
        anchors.top: actionsHeader.bottom
        anchors.topMargin: -5
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        color: Constants.structureColor
        radius: 5
    }
    Rectangle {
        id: actionsHeader
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: 30
        color: Constants.highlightColor
        radius: 5

        Rectangle {
            anchors.fill: parent
            anchors.topMargin: 5
            color: Constants.highlightColor
            radius: 0
        }

        SText {
            padding: 6
            text: "Actions"
            font.bold: true
        }
    }

    Item {
        id: actions
        anchors.fill: actionsContainer
        anchors.margins: 5
        anchors.topMargin: 10
        clip: true
        SComboBox {
            id: actionCombo
            model: ["Generate Key", "Create Stack", "Create Transaction"]
            anchors.left: actions.left
            anchors.right: actions.right
        }

        StackLayout {
            currentIndex: actionCombo.currentIndex
            anchors.left: actions.left
            anchors.right: actions.right
            anchors.top: actionCombo.bottom
            id: parameters


            Item {}
            StackParameters {
                id: createStack
            }
            TxParameters {
                id: createTx
            }
        }


        SButton {
            anchors.left: actions.left
            anchors.right: actions.right
            anchors.bottom: actions.bottom
            anchors.topMargin: 5
            font.bold: true
            text: "Go!"
        }
    }
}
