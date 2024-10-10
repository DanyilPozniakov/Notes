import QtQuick

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")


    Item {
        id: noteEditor
        width: 500
        height: 250

        Rectangle{
            anchors.fill: parent
            border.width: 2
            border.color: "black"
            TextEdit{
                anchors.fill: parent
                wrapMode: TextEdit.Wrap



            }
        }


    }


}
