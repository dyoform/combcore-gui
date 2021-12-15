import QtQuick 2.12
import QtQuick.Controls 2.12
import "../"

TextEdit {
    id: textMono
    readOnly: true
    wrapMode: Text.WordWrap
    selectByMouse: true
    color: Constants.textColor
    font.family: "Roboto Mono [GOOG]"
}
