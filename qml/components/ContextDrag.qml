import QtQuick 2.0


Rectangle {
    readonly property int start: 200
    readonly property int min: 50
    readonly property real max: 0.3 //percent of screen width

    width: 10
    color: "transparent"
    anchors.right: parent.right
    anchors.top: parent.top
    anchors.bottom: parent.bottom
    anchors.rightMargin: start

    MouseArea {
        anchors.fill: parent
        anchors.bottomMargin: 0
        anchors.topMargin: 0
        drag.target: parent

        drag.minimumX: parent.parent.width * (1-max)
        drag.maximumX: parent.parent.width - min

        //break right anchor
        onPressed: {
            parent.anchors.right = undefined
        }
        //recreate right anchor
        onReleased: {
            parent.anchors.rightMargin = parent.parent.width-(parent.x+parent.width)
            parent.anchors.right = parent.parent.right;
        }
    }
}
