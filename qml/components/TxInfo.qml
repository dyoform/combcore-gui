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
            text: "Source"
        }


        SRectangle {
            width: container.width-105
            height: 20
            color: Constants.highlightColor
            STextMono {
                leftPadding: 5
                id: source
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
                leftPadding: 5
                id: destination
            }
        }

        SText {
            width: 100
            height: 20
            text: "Signature"
        }

        SList {
            id: signature
            width: container.width-105
            height: 100
        }

        Connections {
            target: table
            function onSelectedConstructChanged() {
                if(table.selectedType == 3) {
                    destination.text = table.selectedConstruct.destination
                    source.text = table.selectedConstruct.source
                    signature.model = table.selectedConstruct.signature
                }
            }
        }
    }
}
