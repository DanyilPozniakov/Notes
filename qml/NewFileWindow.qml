import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15


Window {
    id: newFileWindow
    title: "Create new file..."
    width: 400
    height: 250
    visible: false


    ColumnLayout {
        anchors.fill: parent
        RowLayout{
            spacing: 50
            Layout.leftMargin: 50
            Layout.rightMargin: 50
            Layout.maximumHeight: 50
            Text{
                text: "Name:"
                color: "#d5d5d5"
                font.pixelSize: 25
            }
           /* Item{ //Spacer
                Layout.fillWidth: true
            }*/
            Rectangle{
                color:"#6de454"
                Layout.fillWidth: true
                Layout.fillHeight: true
                
                TextInput{
                    id: fileName
                    font.pixelSize:20
                    color: "#d5d5d5"

                }
            }
        }

        Item{
            Layout.fillWidth: true
            Layout.fillHeight: true
            Rectangle {
                anchors.fill:parent
                color: "#1e1f22"

            }
        }
    }

}
