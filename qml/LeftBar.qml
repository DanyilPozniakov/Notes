import QtQuick
import QtQuick.Controls
import QtQuick.Layouts



Rectangle{
    id: leftBar
    property bool addingCategory: false

    ColumnLayout {
        anchors.fill: parent

        RowLayout {
            Layout.fillWidth: true
            height: 40
            //color: "transparent"
            spacing: 10
            Text {
                id: tNotes
                anchors.left: parent
                text: "HOME"
                font.family: "JetBrains Mono"
                font.pixelSize: 40
                color: "#93fff2"
            }

            Button {
                id: newCategory
                text: "+"
                font.pixelSize: 20
                onClicked: {
                    addingCategory = !addingCategory
                }
            }

        }
        Rectangle {
            id: writeNewCategory
            Layout.fillWidth: true
            height: addingCategory ? 40 : 0
            color: "#a12323"
            border.width: 1
            radius: 4

            Behavior on height {
                NumberAnimation { duration: 100 }
            }

            TextInput {
                id: newCategoryName
                anchors.fill: parent
                focus: addingCategory
                color: "#30a557"
                font.pixelSize: 24
                onAccepted: {
                    addingCategory = false
                    categoryView.model.append({name: newCategoryName.text})
                    newCategoryName.text = ""
                }
            }
            

        }
        //listNOde
        Rectangle {
            id:noteList
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "transparent"
            border.width: 1
            border.color: "#dfdfdf"
            radius: 5

            ListView {
                id: categoryView
                anchors.fill: parent
                model: ListModel {
                    ListElement { name: "Category1" }
                    ListElement { name: "Category2" }
                    ListElement { name: "Category3" }
                    ListElement { name: "Category4" }
                }

                delegate: Item {
                    width: categoryView.width
                    height: 35
                    Rectangle {
                        anchors.fill: parent
                        color: "transparent"
                        Text {
                            anchors.left: parent
                            text: name
                            font.pixelSize: 17
                            color: "white"
                        }
                    }
                }
            }
        }
    }
}
