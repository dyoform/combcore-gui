import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.12

import combcore 1.0
import combcore.gui 1.0

import "../style"
import "../"

Item {
    property GenerateKeyAction thisAction: GUI.action.generateKeyAction
    id: container
    Grid {
        id: grid
        padding: 5
        columns: 2
        spacing: 2

        SText {
            width: 100
            height: 20
            text: "Public"
        }


        SRectangle {
            width: container.width-105
            height: 20
            color: Constants.dimHighlightColor
            STextMono {
                anchors.fill: parent
                text: thisAction.publicKey
                leftPadding: 5
            }
        }

        SText {
            width: 100
            height: 20
            text: "Private"
        }

        SList {
            width: container.width-105
            height: 200
            model: thisAction.privateKey
            visible: thisAction.privateKey.length !== 0
        }

        SRectangle {
            width: container.width-105
            height: 20
            color: Constants.dimHighlightColor
            visible: thisAction.privateKey.length === 0
        }

        SText {
            width: 100
            height: 20
            text: ""
            visible: thisAction.privateKey.length !== 0
        }

        SButton {
            width: 100
            height: 20
            text: "Store"
            enabled: thisAction.stored === false;
            visible: thisAction.privateKey.length !== 0
            onPressed: {
                thisAction.saveKey()
            }
        }

    }

    SRectangle {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: goButton.top
        height: 20
        color: "red"
        visible: thisAction.error != ""
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
            thisAction.generateNew()
        }
    }
}

