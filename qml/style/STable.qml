import QtQuick 2.15
import QtQuick.Controls 2.15
import "../"
Item {
    id: table
    property var widthProvider
    property var model
    clip: true

    focus: true
    Keys.onUpPressed: table.model.selectedRow--;
    Keys.onDownPressed: table.model.selectedRow++;

    HorizontalHeaderView {
        id: tableHeader
        anchors.fill: parent
        syncView: tableView

        clip: true
        boundsBehavior: Flickable.StopAtBounds

        ScrollBar.vertical: ScrollBar { }

        model: parent.model

        columnWidthProvider: parent.widthProvider

        delegate: Rectangle {
            color: Constants.accentColor
            implicitHeight: 20
            radius: 1

            SText {
                anchors.left: parent.left
                anchors.leftMargin: 5
                anchors.right: parent.right
                anchors.rightMargin: 5
                text: display
                font.bold: true
            }

        }

        onWidthChanged: {
            forceLayout()
        }
    }

    TableView {

        id: tableView
        anchors.fill: parent
        anchors.topMargin: 20
        clip: true
        boundsBehavior: Flickable.StopAtBounds

        ScrollBar.vertical: ScrollBar {

        }

        model: parent.model

        columnWidthProvider: parent.widthProvider

        delegate: Rectangle {
            color: table.model.selectedRow == row ? Constants.lightAccentColor: (row % 2 == 0 ? Constants.highlightColor : Constants.seperatorColor)
            implicitHeight: 20
            clip: true
            MouseArea {
                propagateComposedEvents: true
                anchors.fill: parent
                onClicked: {
                    table.model.selectedRow = row
                    tableView.forceLayout()
                    mouse.accepted = false
                }
            }
            STextMono {
                id: textField
                anchors.left: parent.left
                anchors.leftMargin: 5
                anchors.right: parent.right
                anchors.rightMargin: 5
                text: "" + display
                onSelectedTextChanged: {
                    table.model.selectedRow = row
                    tableView.forceLayout()
                }
                onFocusChanged: {
                    if(focus) {
                        table.model.selectedRow = row
                        tableView.forceLayout()
                    }
                }

            }

        }

        onWidthChanged: {
            forceLayout()
        }
    }

}
