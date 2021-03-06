pragma Singleton
import QtQuick 2.6

QtObject {

    readonly property color backgroundColor: "#212121"
    readonly property color darkStructureColor: "#282828"
    readonly property color structureColor: "#313131"
    readonly property color seperatorColor: "#2c2c2c"
    readonly property color highlightColor: "#424242"
    readonly property color dimHighlightColor: "#373737"
    readonly property color menuColor: "#464646"
    readonly property color textColor: "#c2c2c2"
    readonly property color darkTextColor: "#252525"
    readonly property color buttonColor: "#313131"
    readonly property color iconColor: "#e0e0e0"

    property color lighterAccentColor: "#d692d1"
    property color lightAccentColor: "#af5bd9"
    property color accentColor: "#a338d9"
    property color dimAccentColor: "#9100d9"
    property color darkAccentColor: "#7e00bd"

    property string title: qsTr("COMBCore")
}
