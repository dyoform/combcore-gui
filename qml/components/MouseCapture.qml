import QtQuick 2.0

MouseArea {
    anchors.fill: parent
    hoverEnabled: true
    propagateComposedEvents: true

    //dont eat the events!
    onPositionChanged: mouse.accepted = false;
    onClicked: mouse.accepted = false;
    onPressed: mouse.accepted = false;
    onReleased: mouse.accepted = false;
    onDoubleClicked: mouse.accepted = false;
    onPressAndHold: mouse.accepted = false;
}
