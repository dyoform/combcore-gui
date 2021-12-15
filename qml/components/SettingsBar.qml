import QtQuick 2.12
import QtQuick.Controls 2.12

import "../style"
import "../"

SMenuBar {
    SMenu {
        title: qsTr("File")
        Action { text: qsTr("Load Wallet");}
        Action { text: qsTr("Save Wallet");}
        SMenuSeperator {}
        Action { text: qsTr("Exit");}
    }
    SMenu {
        title: qsTr("Help")
        Action { text: qsTr("Empty");}
    }
}
