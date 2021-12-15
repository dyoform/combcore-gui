import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.12

import combcore 1.0
import combcore.gui 1.0

import "../style"
import "../"

Item {
    id: container
    clip: true
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


        Rectangle {
            width: container.width-105
            height: 20
            color: Constants.highlightColor
            STextMono {
                leftPadding: 5
                id: publicKey
            }
        }

        SText {
            width: 100
            height: 20
            text: "Balance"
        }

        Rectangle {
            width: container.width-105
            height: 20
            color: Constants.highlightColor
            STextMono {
                leftPadding: 5
                id: balance
            }
        }
        Connections {
            target: GUI.walletTable
            function onSelectedConstructChanged() {
                if(GUI.walletTable.selectedType == 1) {
                    publicKey.text = GUI.walletTable.selectedConstruct.publicKey
                    balance.text = GUI.walletTable.selectedConstruct.balance
                }
            }
        }
    }
}
