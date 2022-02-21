import QtQuick 2.0

Item {
    id: container
    clip: true
    property Item activeItem: null
    required property int activeIndex
    property int offset: 0
    onActiveIndexChanged: {
        offset = container.height * activeIndex

    }
    Behavior on offset  {
        NumberAnimation {
            duration: 100
            easing.type: Easing.InOutQuad
        }
    }
}
