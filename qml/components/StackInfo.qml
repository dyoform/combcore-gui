import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.12

import combcore 1.0
import combcore.gui 1.0

import "../style"
import "../"

Item {
    property WalletTable table: GUI.wallet.walletTable
    property bool hasBalance: true
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
            text: "Balance"
            visible: hasBalance
        }

        SRectangle {
            width: container.width-105
            height: 20
            color: Constants.highlightColor
            visible: hasBalance
            STextMono {
                leftPadding: 5
                id: balance
            }
        }

        SText {
            width: 100
            height: 20
            text: "Change"
        }

        SRectangle {
            width: container.width-105
            height: 20
            color: Constants.highlightColor
            STextMono {
                id: change
                leftPadding: 5
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
                id: destination
                leftPadding: 5
            }
        }

        SText {
            width: 100
            height: 20
            text: "Sum"
        }

        SRectangle {
            width: container.width-105
            height: 20
            color: Constants.highlightColor
            STextMono {
                id: sum
                leftPadding: 5
            }
        }
        Connections {
            target: table
            function onSelectedConstructChanged() {
                if(table.selectedType == 2) {
                    destination.text = table.selectedConstruct.destination
                    change.text = table.selectedConstruct.change
                    sum.text = table.selectedConstruct.sum
                    balance.text = table.selectedConstruct.balance
                    hasBalance = !table.selectedConstruct.active
                }
            }
        }
    }
}
