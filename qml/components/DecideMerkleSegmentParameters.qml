import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.15

import combcore 1.0
import combcore.gui 1.0

import "../style"
import "../"

Item {
    property DecideMerkleSegmentAction thisAction: GUI.action.decideMerkleSegmentAction
    id: container
    Grid {
        id: grid
        padding: 5
        columns: 2
        spacing: 2

        SText {
            width: 100
            height: 20
            text: "Address"
        }

        SRectangle {
            width: container.width-105
            height: 20
            color: thisAction.got ? Constants.dimHighlightColor : Constants.highlightColor
            STextMono {
                readOnly: thisAction.got
                anchors.fill: parent
                text: thisAction.address
                onTextEdited: {
                    thisAction.address = text
                }
                leftPadding: 5
            }
        }

        SText {
            width: 100
            height: 20
            text: "Signature"
        }

        SRectangle {
            width: container.width-105
            height: 20
            color: thisAction.got ? Constants.dimHighlightColor : Constants.highlightColor
            STextMono {
                readOnly: thisAction.got
                anchors.fill: parent
                text: thisAction.signature1
                onTextEdited: {
                    thisAction.signature1 = text
                }
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
            color: thisAction.got ? Constants.dimHighlightColor : Constants.highlightColor
            STextMono {
                readOnly: thisAction.got
                anchors.fill: parent
                text: thisAction.signature2
                onTextEdited: {
                    thisAction.signature2 = text
                }
                leftPadding: 5
            }
        }

        SText {
            width: 100
            height: 20
            text: "Leaf"
        }

        SRectangle {
            width: container.width-105
            height: 20
            color: thisAction.got ? Constants.dimHighlightColor : Constants.highlightColor
            STextMono {
                readOnly: thisAction.got
                anchors.fill: parent
                text: thisAction.leaf
                onTextEdited: {
                    thisAction.leaf = text
                }
                leftPadding: 5
            }
        }

        SText {
            width: 100
            height: 20
            text: "Branches"
        }

        SRectangle {
            width: container.width-105
            height: 20
            color: Constants.highlightColor
            visible: !thisAction.got
            STextMono {
                readOnly: false
                anchors.fill: parent
                text: thisAction.branchesString
                onTextEdited: {
                    thisAction.branchesString = text
                }
                leftPadding: 5
            }
        }

        SList {
            width: container.width-105
            height: 150
            model: thisAction.branches
            visible: thisAction.got
        }

        SText {
            width: 100
            height: 20
            text: "Tips"
            visible: thisAction.got
        }

        SRectangle {
            width: container.width-105
            height: 20
            color: Constants.dimHighlightColor
            visible: thisAction.got
            STextMono {
                anchors.fill: parent
                text: thisAction.tips.length === 2 ? thisAction.tips[0] : ""
                leftPadding: 5
            }
        }

        SText {
            width: 100
            height: 20
            text: ""
            visible: thisAction.got
        }

        SRectangle {
            width: container.width-105
            height: 20
            color: Constants.dimHighlightColor
            visible: thisAction.got
            STextMono {
                anchors.fill: parent
                text: thisAction.tips.length === 2 ? thisAction.tips[1] : ""
                leftPadding: 5
            }
        }

        SText {
            width: 100
            height: 20
            text: "Next"
            visible: thisAction.got
        }


        SRectangle {
            width: container.width-105
            height: 20
            color: Constants.dimHighlightColor
            visible: thisAction.got
            STextMono {
                anchors.fill: parent
                text: thisAction.next
                leftPadding: 5
            }
        }

        SText {
            width: 100
            height: 20
            text: ""
            visible: thisAction.got
        }

        RowLayout {
            visible: thisAction.got
            SButton {
                Layout.maximumHeight: 20
                width: 100
                height: 20
                text: "Store"
                enabled: thisAction.stored === false
                onPressed: {
                    thisAction.storeMerkleSegment()
                }
            }
            SButton {
                Layout.maximumHeight: 20
                width: 100
                height: 20
                text: "Clear"
                enabled: thisAction.got
                onPressed: {
                    thisAction.clear()
                }
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
            thisAction.decideMerkleSegment()
        }
    }
}

