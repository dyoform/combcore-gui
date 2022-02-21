import QtQuick 2.12
import QtQuick.Controls 2.12
import "../"

TextField {
    background: Rectangle {
            implicitWidth: 200
            implicitHeight: 20
            color: "transparent"
    }
    padding: 0
    id: textMono
    wrapMode: Text.WordWrap
    selectByMouse: true
    color: Constants.textColor
    font.family: "Roboto Mono [GOOG]"
}
