import QtQuick 2.12
import QtQuick.Controls 2.12
import "../"
ComboBox {
    id: control

    delegate: ItemDelegate {
        width: control.width
        height: 30
        contentItem: Text {
            text: modelData
            color: parent.pressed ? Constants.darkTextColor : Constants.textColor
            font: control.font
            elide: Text.ElideRight
            verticalAlignment: Text.AlignVCenter
        }
        background: Rectangle {
            color: control.highlightedIndex === index ? (parent.pressed ? Constants.iconColor : Constants.accentColor) : Constants.menuColor
        }
        highlighted: control.highlightedIndex === index
    }



    indicator: Canvas {
        id: canvas
        x: control.width - width - control.rightPadding
        y: control.topPadding + (control.availableHeight - height) / 2
        width: 12
        height: 8
        contextType: "2d"

        Connections {
            target: control.popup
            function onVisibleChanged() { canvas.requestPaint(); }
        }

        onPaint: {
            context.reset();
            context.moveTo(0, 0);
            context.lineTo(width, 0);
            context.lineTo(width / 2, height);
            context.closePath();
            context.fillStyle = control.popup.visible ? Constants.iconColor : Constants.accentColor;
            context.fill();
        }
    }

    contentItem: Text {
        leftPadding: 5
        rightPadding: control.indicator.width + control.spacing

        text: control.displayText
        font: control.font
        color: Constants.textColor
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
    }

    background: Rectangle {
        implicitWidth: 120
        implicitHeight: 30
        color: Constants.highlightColor
        radius: 2
    }

    popup: Popup {
        y: control.height
        width: control.width
        implicitHeight: contentItem.implicitHeight+2
        padding: 1

        contentItem: ListView {
            clip: true
            implicitHeight: contentHeight
            model: control.popup.visible ? control.delegateModel : null
            currentIndex: control.highlightedIndex
            ScrollIndicator.vertical: ScrollIndicator { }
        }

        background: Rectangle {
            color: Constants.seperatorColor
            radius: 2
        }
    }
}
