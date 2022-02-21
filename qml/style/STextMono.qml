import QtQuick 2.12
import QtQuick.Controls 2.12
import "../"

TextField {
    padding: 0
    background: Rectangle {
            implicitWidth: 10000
            implicitHeight: 20
            color: "transparent"
    }
    id: textMono
    readOnly: true
    wrapMode: Text.WordWrap
    selectByMouse: true
    color: Constants.textColor
    font.family: "Roboto Mono"
}
