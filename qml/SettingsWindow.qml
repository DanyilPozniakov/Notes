import QtQuick
import QtQuick.Controls

Window {
        id: settingsWindow
        title: "Settings"
        width: 400
        height: 250
        visible: false
        Rectangle{
            color: "white"
            anchors.fill: parent
            Text{
                anchors.centerIn: parent
                text: "New File"
            }
        }
    }
