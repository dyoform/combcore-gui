import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.15

import combcore 1.0
import combcore.gui 1.0

import "../style"
import "../"

Item {
     property SettingsScreen screen: GUI.settings
    Rectangle {
        id: settings
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        color: Constants.structureColor
        radius: 5
        Rectangle {
            id: settingsHeader
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
                text: "Settings"
                font.bold: true
            }

            RoundButton {
                anchors.right: settingsHeader.right
                anchors.rightMargin: 5
                anchors.top: settingsHeader.top
                anchors.topMargin: 5
                background: Rectangle {
                    implicitWidth: 20
                    implicitHeight: 20
                    opacity: enabled ? 1 : 0.3
                    color: parent.pressed ? Constants.darkAccentColor : Constants.accentColor
                    border.width: 0
                    radius: 5
                }
                icon.height: 15
                icon.width: 15
                padding: 0
                icon.source: "qrc:/images/true.svg"
                icon.color: "transparent"

                onPressed: {
                    GUI.settings.save()
                }
            }
        }
        Item {
            id: container
            anchors.fill: parent
            anchors.margins: 5
            anchors.topMargin: 30
            clip: true
            Grid {
                id: grid
                columns: 2
                spacing: 2
                padding: 5

                SText {
                    width: 100
                    height: 20
                    text: "Remote"
                }


                SRectangle {
                    width: container.width-105
                    height: 20
                    color: Constants.highlightColor
                    STextMono {
                        readOnly: false
                        anchors.fill: parent
                        text: screen.remoteAddress
                        onTextEdited: {
                            screen.remoteAddress = text
                        }

                        leftPadding: 5
                    }
                }
                SText {
                    width: 100
                    height: 20
                    text: "Port"
                }


                SRectangle {
                    width: container.width-105
                    height: 20
                    color: Constants.highlightColor
                    STextMono {
                        readOnly: false
                        anchors.fill: parent
                        text: screen.remotePort
                        onTextEdited: {
                            screen.remotePort = parseInt(text)
                        }
                        validator: IntValidator {bottom: 0}

                        leftPadding: 5
                    }
                }

                SText {
                    width: 100
                    height: 20
                    text: "Log"
                }

                SList {
                    width: container.width-105
                    id: log
                    height: container.height - 50
                    model: screen.output
                }
            }
        }
    }
}
