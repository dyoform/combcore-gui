import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.0
import "../style"
import "../"


import combcore 1.0
import combcore.gui 1.0

SMenuBar {
    SMenu {
        FileDialog {
            id: walletLoadDialog
            title: "Load Wallet"
            folder: shortcuts.home
            nameFilters: [ "*.dat" ]
            onAccepted: {
                GUI.wallet.loadWallet(walletLoadDialog.fileUrl)
            }
        }
        FileDialog {
            id: walletSaveDialog
            title: "Save Wallet"
            folder: shortcuts.home
            nameFilters: [ "*.dat" ]
            selectExisting: false
            onAccepted: {
                GUI.wallet.saveWallet(walletSaveDialog.fileUrl)
            }
        }
        title: qsTr("File")
        Action {
            text: qsTr("Load Wallet");
            onTriggered: {
                walletLoadDialog.visible = true
            }


        }
        Action {
            text: qsTr("Save Wallet");
            onTriggered: {
                walletSaveDialog.visible = true
            }
        }
        SMenuSeperator {}
        Action { text: qsTr("Exit");}
    }
    SMenu {
        title: qsTr("Help")
        Action {
            text: qsTr("COMBCore Info");
            onTriggered: {
                GUI.openURL("https://github.com/dyoform/combcore/wiki")
            }
        }
        Action {
            text: qsTr("Haircomb Community");
            onTriggered: {
                GUI.openURL("https://21Teeth.org")
            }
        }
    }
}
