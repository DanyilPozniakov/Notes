import QtQuick
import QtQuick.Controls

MenuBar {
    id: menuBar

    Menu {
        title: "File"
        Action {
            text: "New"
            onTriggered:{
                application.createNewFile("NewFile");
                //TODO: qDialog
            }
        }
        Action { text: "Open" }
        Action { text: "Save" }
        MenuSeparator {}
        Action {
            text: "Setting"
            onTriggered: settingsWindow.visible = true;
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

    // WINDOWS/DIOLOG
    SettingsWindow {
        id: settingsWindow
    }

}
