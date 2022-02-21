import QtQuick 2.12
import QtQuick.Controls 2.12
import "../"

TextField {
    padding: 0
    background: Rectangle {
            implicitHeight: 20
            color: "transparent"
    }
    id: text
    readOnly: true
    selectByMouse: true
    color: Constants.textColor
}
