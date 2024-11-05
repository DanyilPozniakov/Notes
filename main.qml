import QtQuick
import QtQuick.Controls

ApplicationWindow {
    id: window
    width: 1000
    height: 600
    visible: true
    title: qsTr("Hello World")


    TextEdit {
        id : textEditor
        objectName: "textEditor"
        anchors.right: parent.right
        width: 200
        height: 400
    }

}
