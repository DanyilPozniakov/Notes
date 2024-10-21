import QtQuick
import QtQuick.Controls

ApplicationWindow {
    width: 1000
    height: 600
    visible: true
    title: qsTr("Hello World")



    Item {
        id: leftMenuBar
        width: 250
        height: parent.height
        Rectangle {
            color: "#7e95a7"
            anchors.fill: parent
            Row{
                width:parent.width
                height: 50
                anchors.top: parent.top
                spacing: 10


                Rectangle {
                    width: parent.height
                    height: parent.height
                    color: "#c1c1c1"
                }

                Text {
                    text: "Notes"
                    anchors.margins: 10
                    font.pixelSize: 20
                    color: "white"
                }
            }

        }
    }

    NoteEditor {
        id: noteEditor
        anchors.right: parent.right
        height: parent.height
        width: 600
    }
}
