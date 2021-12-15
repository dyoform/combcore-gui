import QtQuick 2.12
import QtQuick.Controls 2.12
import "../"
MenuBar {
    readonly property real menuBarSize: 30
    height: menuBarSize
    contentHeight: menuBarSize

    delegate: MenuBarItem {
            id: menuBarItem
            implicitHeight: menuBarSize
            hoverEnabled: true
            contentItem: Text {
                text: menuBarItem.text
                font: menuBarItem.font
                opacity: enabled ? 1.0 : 0.3
                color: menuBarItem.hovered || menuBarItem.highlighted  ? Constants.darkTextColor : Constants.textColor
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
            }

            background: Rectangle {
                implicitWidth: menuBarSize
                implicitHeight: menuBarSize
                opacity: enabled ? 1 : 0.3
                color: menuBarItem.hovered || menuBarItem.highlighted ?  Constants.accentColor : "transparent"
            }
    }

    background: Rectangle {
        implicitWidth: menuBarSize
        implicitHeight: menuBarSize
        color: Constants.highlightColor
    }
}
