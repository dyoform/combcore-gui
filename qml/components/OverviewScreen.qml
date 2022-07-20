import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

import combcore 1.0
import combcore.gui 1.0

import "../style"
import "../"

Item {
    property OverviewScreen screen: GUI.overview
    Rectangle {
        id: info
        anchors.top: infoHeader.bottom
        anchors.left: infoHeader.left
        anchors.right: infoHeader.right
        anchors.bottom: grid.bottom
        anchors.topMargin: -5
        width: 200
        color: Constants.structureColor
        radius: 5
    }
    Rectangle {
        id: infoHeader
        anchors.top: parent.top
        anchors.left: parent.left
        width: 200
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
            text: "Overview"
            font.bold: true
        }
    }

    Grid {
        clip:true
        id: grid
        padding: 5
        columns: 2
        spacing: 2
        width: 200
        anchors.top: info.top
        anchors.topMargin: 5

        SText {
            text: "Haircomb"
            width: 100
            font.bold: true
        }
        SText {
            text: " "
        }
        SText {
            text: "Height"
        }
        STextMono {
            text: screen.height
        }
        SText {
            text: "Commits"
        }
        STextMono {
            text: screen.commits
        }
        SText {
            text: "Blockchain"
            font.bold: true
        }
        SText {
            text: " "
        }
        SText {
            text: "Height"
        }
        STextMono {
            text: screen.btcHeight
        }
        SText {
            text: "Known Height"
            visible: screen.btcHeight !== screen.btcKnownHeight
        }
        STextMono {
            text: screen.btcKnownHeight
            visible: screen.btcHeight !== screen.btcKnownHeight
        }
        SText {
            text: "Status"
        }
        SText {
            text: screen.btcStatus
        }
    }

    Rectangle {
        id: pending
        anchors.top: pendingHeader.bottom
        anchors.right: pendingHeader.right
        anchors.left: pendingHeader.left
        anchors.bottom: parent.bottom
        anchors.topMargin: -5

        color: Constants.structureColor
        radius: 5
    }

    Rectangle {
        id: pendingHeader
        anchors.top: parent.top
        anchors.left: info.right
        anchors.right: parent.right
        anchors.leftMargin: 5
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
            text: "Pending"
            font.bold: true
        }

        RoundButton {
            anchors.right: clearButton.left
            anchors.rightMargin: 5
            anchors.top: pendingHeader.top
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
            icon.source: "qrc:/images/special.svg"
            icon.color: Constants.lighterAccentColor

            onPressed: {
                screen.getCommand()
            }
        }

        RoundButton {
            anchors.right: pendingHeader.right
            anchors.rightMargin: 5
            anchors.top: pendingHeader.top
            anchors.topMargin: 5
            id: clearButton
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
            icon.source: "qrc:/images/trash.svg"
            icon.color: Constants.lighterAccentColor

            onPressed: {
                screen.clear()
            }
        }
    }

    STable {
        anchors.fill: pending
        anchors.margins: 5
        anchors.topMargin: 10
        widthProvider: function(c) {
            return [pending.width-120 < 0 ? 0 : pending.width-120, 110][c]
        }
        model: screen.pendingTable
    }

    Connections {
        target: screen
        function onNetworkChanged() {
            console.log("network changed to ", screen.network)
            if(screen.network === "testnet") {
                Constants.lighterAccentColor = "#2fc164"
                Constants.lightAccentColor = "#009800"
                Constants.accentColor = "#008700"
                Constants.dimAccentColor = "#00c943"
                Constants.darkAccentColor = "#006500"
                Constants.title = qsTr("COMBCore Testnet")
            } else {
                Constants.lighterAccentColor = "#d692d1"
                Constants.lightAccentColor = "#af5bd9"
                Constants.accentColor = "#a338d9"
                Constants.dimAccentColor = "#9100d9"
                Constants.darkAccentColor = "#7e00bd"
                Constants.title = qsTr("COMBCore")
            }
        }
    }

}
