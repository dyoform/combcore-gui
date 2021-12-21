import QtQuick 2.12
import QtQuick.Controls 2.12
import "../"

TextArea {
    padding: 0
    id: textMono
    readOnly: true
    wrapMode: Text.NoWrap
    selectByMouse: true
    color: Constants.textColor
    font.family: "Roboto Mono [GOOG]"
}
