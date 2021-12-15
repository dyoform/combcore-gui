import QtQuick 2.12
import QtQuick.Controls 2.12
import "../"
Menu {
    readonly property real menuItemSize: 30
    topPadding: 4
    bottomPadding: 4
    delegate: MenuItem {
        id: menuItem
        implicitWidth: 200
        implicitHeight: menuItemSize
        hoverEnabled: true

        contentItem: Text {
            text: menuItem.text
            font: menuItem.font
            opacity: enabled ? 1.0 : 0.3
            color: menuItem.hovered ? Constants.darkTextColor : Constants.textColor
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
        }

        background: Rectangle {
            implicitWidth: 200
            implicitHeight: menuItemSize
            opacity: enabled ? 1 : 0.3
            color: menuItem.hovered ? Constants.accentColor : "transparent"
        }
    }

    background: Rectangle {
        implicitWidth: 200
        implicitHeight: menuItemSize
        color: Constants.menuColor
        radius: 2
    }
}
