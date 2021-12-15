import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

import combcore 1.0
import combcore.gui 1.0

import "../style"
import "../"

Item {
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
        id: grid
        padding: 5
        columns: 2
        spacing: 2

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
            text: "Supply"
        }
        STextMono {
            text: "0 of 0"
        }
        SText {
            text: "Commits"
        }
        STextMono {
            text: "0"
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
            text: "0"
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
            text: "Pending Commits"
            font.bold: true
        }
    }

    STable {
        anchors.fill: pending
        anchors.margins: 5
        anchors.topMargin: 10
        widthProvider: function(c) {
            return [pending.width-110 < 0 ? 0 : pending.width-110, 100][c]
        }
        model: GUI.pendingTable
    }

}
