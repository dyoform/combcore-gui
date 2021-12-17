import QtQuick 2.15
import QtQuick.Controls 2.15
import "../"
Item {
    id: list
    property var model
    clip: true

    ListView {
        id: tableView
        anchors.fill: parent
        boundsBehavior: Flickable.StopAtBounds

        ScrollBar.vertical: ScrollBar {

        }

        model: parent.model

        delegate: Rectangle {
            color: index % 2 == 0 ? Constants.highlightColor : Constants.seperatorColor
            implicitHeight: 20
            implicitWidth: list.width
            clip: true
            STextMono {
                anchors.left: parent.left
                anchors.right: parent.right
                text: modelData

            }

        }

        onWidthChanged: {
            forceLayout()
        }
    }

}
