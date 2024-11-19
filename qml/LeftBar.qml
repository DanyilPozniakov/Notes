import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: leftBar
    width: 300
    height: 600
    color: "#2c2c2c"

    property bool addingCategory: false

    onAddingCategoryChanged: {
        newCategoryName.text = ""
    }

    ColumnLayout {
        anchors.fill: parent

        // HEADER
        RowLayout {
            Layout.fillWidth: true
            height: 40
            spacing: 10

            Text {
                id: tNotes
                text: "NOTES"
                font.family: "JetBrains Mono"
                font.pixelSize: 40
                color: "#dddddd"
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

        // CATEGORY INPUT
        Rectangle {
            id: writeNewCategory
            Layout.fillWidth: true
            height: addingCategory ? 35 : 0
            z: 1
            color: "#a8a8a8"
            opacity: 1
            border.width: 1
            radius: 4

            Behavior on height {
                NumberAnimation { duration: 100 }
            }

            TextInput {
                id: newCategoryName
                anchors.fill: parent
                focus: addingCategory

                font.pixelSize: 24
                maximumLength: 20
                onAccepted: {
                    categoryView.model.append({ name: newCategoryName.text })
                    newCategoryName.text = ""
                    addingCategory = false
                }
            }
        }

        // NOTES TREE
        Rectangle {
            id: noteList
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
                    ListElement { name: "STL + " }
                    ListElement { name: "Algorithms +" }

                    //TODO: realize tree structure
                }

                delegate: Item {
                    width: categoryView.width
                    height: 35
                    Rectangle {
                        anchors.fill: parent
                        color: "transparent"
                        Text {
                            anchors.left: parent.left
                            text: name
                            font.pixelSize: 17
                            color: "white"
                        }
                    }
                }
            }
        }
    }


    //
    MouseArea {
        id: dropWriteCategory
        anchors.fill: leftBar
        z: 2
        visible: addingCategory
        onClicked: {
            addingCategory = false
        }
    }
}
