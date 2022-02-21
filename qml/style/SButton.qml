import QtQuick 2.12
import QtQuick.Controls 2.12
import "../"

RoundButton {
    id: button
    hoverEnabled: true
    background: Rectangle {
        implicitWidth: 40
        implicitHeight: 40
        opacity: enabled ? 1 : 0.3
        color: button.hovered ? Constants.dimAccentColor : (pressed ? Constants.darkAccentColor : Constants.accentColor)
        border.width: 0
        radius: 1
    }
    icon.color: checked || pressed ? Constants.lighterAccentColor :  Constants.iconColor
}
