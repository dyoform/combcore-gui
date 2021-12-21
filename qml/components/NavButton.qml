import QtQuick 2.0
import QtQuick.Controls 2.12
import combcore 1.0
import combcore.gui 1.0

import "../style"
import "../"

RoundButton {
    property ScreenControls controls: GUI.screenControls
    readonly property real buttonSize: 50
    property int guiScreen: GUI.SCREEN_NONE
    width: buttonSize
    height: buttonSize
    checkable: true
    display: AbstractButton.IconOnly
    checked: controls.activeScreen === guiScreen
    onPressed: controls.activeScreen = guiScreen

    background: Rectangle {
        implicitWidth: 50
        implicitHeight: 50
        opacity: enabled ? 1 : 0.3
        color: pressed ? Constants.darkAccentColor : (checked ? Constants.accentColor : Constants.buttonColor)
        border.width: 0
        radius: 0
    }
    icon.color: checked || pressed ? Constants.lighterAccentColor:  Constants.iconColor
}
