import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.15

import combcore 1.0
import combcore.gui 1.0

import "../style"
import "../"

Item {
     property WalletScreen thisScreen: GUI.wallet
    Rectangle {
        id: info
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: details.top
        anchors.bottomMargin: 5
        color: Constants.structureColor
        radius: 5
        Rectangle {
            id: infoHeader
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
                text: "Wallet"
                font.bold: true
            }
            /*Rectangle {
                anchors.right: infoHeader.right
                anchors.rightMargin: 5
                anchors.top: infoHeader.top
                anchors.topMargin: 5
                width: 600
                height: 20
                radius: 2
                color: Constants.structureColor
                SInputMono {
                    anchors.fill: parent
                    readOnly: false
                    id: search
                    leftPadding: 5
                    placeholderText: "Search"
                    text: "Search"
                    onTextChanged: {
                        console.log(text)
                    }
                }
            }*/
        }

        STable {
            anchors.fill: info
            anchors.margins: 5
            anchors.topMargin: 35
            widthProvider: function(c) {
                return [120, 60, info.width-190][c]
            }
            model: thisScreen.walletTable
        }
    }
    Rectangle {
        id: details
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        height: 200
        color: Constants.structureColor
        radius: 5
        Rectangle {
            id: detailsHeader
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
                text: ["None", "Key", "Stack", "Transaction"][thisScreen.walletTable.selectedType]
                font.bold: true
            }
        }

        StackLayout {
            anchors.fill: details
            anchors.margins: 5
            anchors.topMargin: 35

            currentIndex: thisScreen.walletTable.selectedType-1

            KeyInfo {

            }
            StackInfo {
            }
            TxInfo {
            }

        }
        Component.onCompleted: {
            thisScreen.walletTable.selectedRow = 0
        }

    }
}
