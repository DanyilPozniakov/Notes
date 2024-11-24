import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import CategoryModel 1.0

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

        // CATEGORY ADD INPUT
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
                    categoryModel.addCategory(newCategoryName.text)
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

            CategoryModel {
                id: categoryModel
            }

            ListView {
                id: categoryView
                anchors.fill: parent
                model: categoryModel

                delegate: Item {
                    width: parent.width
                    height: files.length * 35 + 35

                    property int categoryIndex: index

                    Column {
                        anchors.fill: parent
                        //CATEGORY ->
                        Row{
                            width: parent.width
                            height: 35

                            Text{
                                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                                Layout.leftMargin: 20
                                anchors.leftMargin: 10
                                text: categoryName
                                font.pixelSize: 17
                                color: "white"
                            }

                            Item{
                                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                                Layout.rightMargin: 20
                                height: parent.height
                                width: height
                                Text{
                                    anchors.centerIn: parent
                                    text:'+'
                                    font.pixelSize: 17
                                    color: "#c1c1c1"
                                }
                                MouseArea{
                                    anchors.fill: parent
                                    onClicked:{
                                        categoryModel.addNoteToCategory(index, "New Note");
                                    }
                                }
                            }
                        }
                        //REPEATER: CATEGORY -> NOTES
                        Repeater {
                            model: files
                            delegate: Rectangle {
                                width: parent.width
                                height: 35
                                color: "transparent"
                                border.width: 1
                                border.color: "#dfdfdf"
                                //NOTE ->
                                Row{
                                    width: parent.width
                                    height: 35
                                    Text {
                                        text: modelData.name
                                        Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                                        Layout.leftMargin: 20
                                        font.pixelSize: 15
                                        color: "white"
                                    }
                                    Button{
                                        text:"delete"
                                        Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                                        Layout.rightMargin: 20
                                        onClicked:{
                                            console.log(categoryIndex,index)
                                            categoryModel.removeNoteFromCategory(categoryIndex,index)
                                        }
                                    }

                                    MouseArea{
                                        onDoubleClicked:{
                                            //TODO: current file logic
                                        }
                                    }
                                }

                            }
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
