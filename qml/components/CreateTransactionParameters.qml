import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.12

import combcore 1.0
import combcore.gui 1.0

import "../style"
import "../"

Item {
    property CreateTransactionAction thisAction: GUI.action.createTransactionAction
    id: container
    Grid {
        id: grid
        padding: 5
        columns: 2
        spacing: 2

        SText {
            width: 100
            height: 20
            text: "Source"
        }

        SRectangle {
            width: container.width-105
            height: 20
            color: Constants.highlightColor
            STextMono {
                readOnly: false
                anchors.fill: parent
                text: thisAction.source
                leftPadding: 5
                onTextEdited: {
                    thisAction.source = text
                }
            }
        }

        SText {
            width: 100
            height: 20
            text: "Destination"
        }

        SRectangle {
            width: container.width-105
            height: 20
            color: Constants.highlightColor
            STextMono {
                readOnly: false
                anchors.fill: parent
                text: thisAction.destination
                onTextEdited: {
                    thisAction.destination = text
                }
                leftPadding: 5
            }
        }

        SText {
            width: 100
            height: 20
            text: "Signature"
        }

        SList {
            width: container.width-105
            height: 200
            model: thisAction.signature
            visible: thisAction.signature.length !== 0
        }

        SRectangle {
            width: container.width-105
            height: 20
            color: Constants.highlightColor
            visible: thisAction.signature.length === 0
        }

        SText {
            width: 100
            height: 20
            text: ""
            visible: thisAction.signature.length !== 0
        }

        SButton {
            width: 100
            height: 20
            text: "Store"
            enabled: thisAction.stored === false;
            visible: thisAction.signature.length !== 0
            onPressed: {
                thisAction.loadTransaction()
            }
        }

    }

    SRectangle {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: goButton.top
        height: 20
        color: "red"
        visible: thisAction.error !== ""
        SText {
            anchors.fill: parent
            font.bold: true
            text: thisAction.error
        }
    }

    SButton {
        id: goButton
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.topMargin: 5
        font.bold: true
        text: "Go!"
        onPressed: {
            thisAction.createTransaction()
        }
    }
}

