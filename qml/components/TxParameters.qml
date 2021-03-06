import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.12

import combcore 1.0
import combcore.gui 1.0

import "../style"
import "../"

Item {
    id: container
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


        Rectangle {
            width: container.width-105
            height: 20
            color: Constants.highlightColor
            STextMono {
                anchors.fill: parent
                readOnly: false
                id: source
                leftPadding: 5
                placeholderText: "Source"
            }
        }

        SText {
            width: 100
            height: 20
            text: "Destination"
        }

        Rectangle {
            width: container.width-105
            height: 20
            color: Constants.highlightColor
            STextMono {
                anchors.fill: parent
                readOnly: false
                id: destination
                leftPadding: 5
                placeholderText: "Destination"
            }
        }
    }

}
