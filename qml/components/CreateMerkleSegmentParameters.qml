import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.12

import combcore 1.0
import combcore.gui 1.0

import "../style"
import "../"

Item {
    property CreateMerkleSegmentAction thisAction: GUI.action.createMerkleSegmentAction
    id: container
    Grid {
        id: grid
        padding: 5
        columns: 2
        spacing: 2

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
                readOnly: false
                anchors.fill: parent
                text: thisAction.tip1
                onTextEdited: {
                    thisAction.tip1 = text
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
            color: Constants.highlightColor
            STextMono {
                readOnly: false
                anchors.fill: parent
                text: thisAction.tip2
                onTextEdited: {
                    thisAction.tip2 = text
                }
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
                readOnly: false
                anchors.fill: parent
                text: thisAction.next
                onTextEdited: {
                    thisAction.next = text
                }
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
                readOnly: false
                anchors.fill: parent
                text: thisAction.root
                onTextEdited: {
                    thisAction.root = text
                }
                leftPadding: 5
            }
        }

        SText {
            width: 100
            height: 20
            text: "Address"
            visible: thisAction.address !== ""
        }


        SRectangle {
            width: container.width-105
            height: 20
            color: Constants.highlightColor
            visible: thisAction.address !== ""
            STextMono {
                anchors.fill: parent
                text: thisAction.address
                leftPadding: 5
            }
        }

        SText {
            width: 100
            height: 20
            text: ""
            visible: thisAction.address !== ""
        }

        SButton {
            width: 100
            height: 20
            text: "Store"
            enabled: thisAction.stored === false;
            visible: thisAction.address !== ""
            onPressed: {
                thisAction.loadUnsignedMerkleSegment()
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
            thisAction.createUnsignedMerkleSegment()
        }
    }
}

