import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.12

import combcore 1.0
import combcore.gui 1.0

import "../style"
import "../"

Item {
    property WalletTable table: GUI.wallet.walletTable
    property bool hasSignature: false
    property bool hasBalance: true
    id: container
    clip: true
    ScrollView {
        anchors.fill: parent
        contentWidth: 0
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
            text: "Tips"
        }

        SRectangle {
            width: container.width-105
            height: 20
            color: Constants.highlightColor
            STextMono {
                id: tip1
                leftPadding: 5
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
                id: tip2
                leftPadding: 5
            }
        }

        SText {
            width: 100
            height: 20
            text: "Next"
        }


        SRectangle {
            width: container.width-105
            height: 20
            color: Constants.highlightColor
            STextMono {
                id: next
                leftPadding: 5
            }
        }

        SText {
            width: 100
            height: 20
            text: "Root"
        }

        SRectangle {
            width: container.width-105
            height: 20
            color: Constants.highlightColor
            STextMono {
                id: root
                leftPadding: 5
            }
        }

        SText {
            width: 100
            height: 20
            text: "Leaf"
            visible: hasSignature
        }

        SRectangle {
            width: container.width-105
            height: 20
            color: Constants.highlightColor
            STextMono {
                id: leaf
                leftPadding: 5
            }
            visible: hasSignature
        }

        SText {
            width: 100
            height: 20
            text: "Signature"
            visible: hasSignature
        }

        SRectangle {
            width: container.width-105
            height: 20
            color: Constants.highlightColor
            STextMono {
                id: signature1
                leftPadding: 5
            }
            visible: hasSignature
        }

        SText {
            width: 100
            height: 20
            text: ""
            visible: hasSignature
        }

        SRectangle {
            width: container.width-105
            height: 20
            color: Constants.highlightColor
            STextMono {
                id: signature2
                leftPadding: 5
            }
            visible: hasSignature
        }

        SText {
            width: 100
            height: 20
            text: "Branches"
            visible: hasSignature
        }


        SList {
            id: branches
            width: container.width-105
            height: 100
            visible: hasSignature
        }

        Connections {
            target: table
            function onSelectedConstructChanged() {
                if(table.selectedType == 5) {
                    balance.text = table.selectedConstruct.balance
                    tip1.text = table.selectedConstruct.tips[0]
                    tip2.text = table.selectedConstruct.tips[1]
                    next.text = table.selectedConstruct.next
                    root.text = table.selectedConstruct.root

                    if(table.selectedConstruct.leaf !== "") {
                        hasSignature = true
                        leaf.text = table.selectedConstruct.leaf
                        signature1.text = table.selectedConstruct.signature[0]
                        signature2.text = table.selectedConstruct.signature[1]
                        branches.model = table.selectedConstruct.branches
                    } else {
                        hasSignature = false
                    }

                    hasBalance = !table.selectedConstruct.active
                }
            }
        }
    }
    }
}
