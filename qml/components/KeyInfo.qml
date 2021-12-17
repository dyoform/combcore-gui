import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.12

import combcore 1.0
import combcore.gui 1.0

import "../style"
import "../"

Item {
    property WalletTable table: GUI.wallet.walletTable
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


        SRectangle {
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

        SRectangle {
            width: container.width-105
            height: 20
            color: Constants.highlightColor
            STextMono {
                leftPadding: 5
                id: balance
            }
        }
        Connections {
            target: table
            function onSelectedConstructChanged() {
                if(table.selectedType == 1) {
                    publicKey.text = table.selectedConstruct.publicKey
                    balance.text = table.selectedConstruct.balance
                }
            }
        }
    }
}
