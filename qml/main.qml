import QtQuick
import QtQuick.Controls
import QtQuick.Layouts



ApplicationWindow {
    id: window
    width: 1200
    height: 750
    visible: true
    title: qsTr("Notes")
    color: "#1e1f22"


    header: TopMenuBar{
        id: topMenuBar
        height: 35
    }

    footer: Rectangle{
        height: 25
        color: "#3c3f40"
        border.width: 1
        border.color: "#505050"
        Text{
            anchors.centerIn: parent
            text: "Footer"
            color: "white"
        }
    }

    NoteEditor {
        id: noteEditor
        anchors.right: parent.right
        anchors.left: leftBar.right
        width: 400
        height: parent.height
    }

    LeftBar {
        id: leftBar
        anchors.left: parent.left
        color: "#3c3f40"
        height: parent.height
        width: 350
    }

}







