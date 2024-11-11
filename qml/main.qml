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

    header: TopMenuBar {
        id: menuBar
        height: 25
    }
    NoteEditor {
        id: noteEditor
        anchors.right: parent.right
        anchors.left: leftBar.right
        width: 400
        height: parent.height
    }

    Rectangle{
        id: leftBar
        color: "#3c3f40"
        anchors.left: parent.left
        width: 250
        height: parent.height


    }




    Dialog {
        id:settingDialog
        title: "Settings"
        modal: true

        width: 400
        height: 250
    }
}
