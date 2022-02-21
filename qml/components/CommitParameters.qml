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
            text: "Address"
        }


        Rectangle {
            width: container.width-105
            height: 20
            color: Constants.highlightColor
            STextMono {
                validator: RegExpValidator { regExp: /[0-9A-F]+/ }
                anchors.fill: parent
                readOnly: false
                id: target
                leftPadding: 5
                placeholderText: "Address"
            }
        }
    }

    function go() {
        GUI.commitAddress(target.text)
    }

}
