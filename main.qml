import QtQuick
import QtQuick.Controls













ApplicationWindow {
    id: window
    width: 1000
    height: 600
    visible: true
    title: qsTr("Hello World")
    color: "#1e1f22"
    //flags: Qt.FramelessWindowHint

    header: MenuBar {
        id: menuBar
        height: 25
        Menu {
            title: "File"
            Action { text: "New" }
            Action { text: "Open" }
            Action { text: "Save" }
            MenuSeparator {}
            Action {
                text: "Setting"
                onTriggered: settingDialog.open();
            }
            Action { text: "Quit" }
        }
        Menu {
            title: "Edit"
            Action { text: "Undo" }
            Action { text: "Redo" }
            MenuSeparator {}
            Action { text: "Cut" }
            Action { text: "Copy" }
            Action { text: "Past" }

        }
        Menu {
            title: "About"
        }

    }




    Dialog {
        id:settingDialog
        title: "Settings"
        modal: true

        width: 400
        height: 250
    }



    NoteEditor {
        id: noteEditor
        anchors.fill: parent
    }

}
