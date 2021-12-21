import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.12

import combcore 1.0
import combcore.gui 1.0

import "../style"
import "../"

Item {
    property CommandAction thisAction: GUI.action.commandAction
    id: container
    Grid {
        id: grid
        padding: 5
        columns: 2
        spacing: 2

        SText {
            width: 100
            height: 20
            text: "Method"
        }


        SRectangle {
            width: container.width-105
            height: 20
            color: Constants.highlightColor
            STextMono {
                readOnly: false
                anchors.fill: parent
                text: thisAction.method
                onTextEdited: {
                    thisAction.method = text
                }

                leftPadding: 5
            }
        }

        SText {
            width: 100
            height: 20
            text: "Parameters"
        }


        SRectangle {
            width: container.width-105
            height: Math.max(20, (container.height-74)/2)
            color: Constants.highlightColor
            clip: true
            ScrollView {
                anchors.fill: parent
                STextMonoMulti {
                    readOnly: false
                    text: thisAction.params
                    onTextChanged: {
                        thisAction.params = text
                    }
                    leftPadding: 5
                }
            }
        }

        SText {
            width: 100
            height: 20
            text: "Response"
            visible: thisAction.result !== ""
        }


        SRectangle {
            width: container.width-105
            height: Math.max(20, (container.height-74)/2)
            color: Constants.highlightColor
            visible: thisAction.result !== ""
            clip: true
            ScrollView {
                anchors.fill: parent
                STextMonoMulti {
                    readOnly: true
                    text: thisAction.result
                    leftPadding: 5
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
        visible: thisAction.error !== ""
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
            thisAction.sendCommand()
        }
    }
}

