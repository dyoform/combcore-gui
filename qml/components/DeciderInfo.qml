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
            text: "ID"
        }


        SRectangle {
            width: container.width-105
            height: 20
            color: Constants.highlightColor
            STextMono {
                leftPadding: 5
                id: id
            }
        }

        SText {
            width: 100
            height: 20
            text: "Tips"
        }

        SRectangle {
            width: container.width-105
            height: 20
            color: Constants.highlightColor
            STextMono {
                leftPadding: 5
                id: tip1
            }
        }
        SText {
            width: 100
            height: 20
            text: ""
        }

        SRectangle {
            width: container.width-105
            height: 20
            color: Constants.highlightColor
            STextMono {
                leftPadding: 5
                id: tip2
            }
        }
        Connections {
            target: table
            function onSelectedConstructChanged() {
                if(table.selectedType == 4) {
                    id.text = table.selectedConstruct.id
                    tip1.text = table.selectedConstruct.tips[0]
                    tip2.text = table.selectedConstruct.tips[1]
                }
            }
        }
    }
}
