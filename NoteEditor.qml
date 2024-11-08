import QtQuick 2.15
import QtQuick.Controls 2.15


Item {
        id: noteEditor
        Rectangle{
            anchors.fill: parent
            border.width: 1
            border.color: "#1E1F22FF"
            radius: 4
            color: "#1e1f22"


            TextEdit{
                id: textEdit
                objectName: "textEditor"
                anchors.fill: parent
                wrapMode: TextEdit.Wrap
                font.family: "JetBrains Mono"
                font.pixelSize: 15
                color: "#dedede"
                textMargin: 10

                Keys.onPressed: (event) => {
                    if(event.key === Qt.Key_Return || event.key === Qt.Key_Backspace){
                        event.accepted = textHandler.onHandleKeyPress(event.key,event.modifiers)
                    }
                }

                onCursorPositionChanged: {
                    textHandler.m_cursor = textEdit.cursorPosition
                }

            }

            // Rectangle {
            //     id: suggestionsView
            //     z: 5
            //     width: 150
            //     height: 75
            //     opacity: 0.4
            //     color: "white"
            //     border.width: 1
            //     border.color: "#aeb6bf"
            //     radius: 4
            //     visible: false

            //     ListView {
            //         id: suggestionsViewList
            //         anchors.fill: parent
            //         model: textHandler.currentSuggestions
            //         delegate: Text {
            //             text: modelData
            //             font.pixelSize: 12
            //             color: "black"
            //         }
            //     }
            // }

            Connections{
                target: textHandler
                function onCursorUpdated(cursorPos) {
                    textEdit.cursorPosition = cursorPos;
                }
                
                // function onInsertText(cursorPos, text) {
                //     var cursor = cursorPos === 0 ? textEdit.cursorPosition : cursorPos;
                //     textEdit.insert(cursor,text);
                // }
                // function onUpdateCursorPosition(cursorPos) {
                //     textEdit.cursorPosition = cursorPos;
                // }
                // function onDeleteText(start,end) {
                //     textEdit.remove(start,end);
                // }
            }
        }

        // function showSuggestions(suggestions) {
        //     suggestionsView.visible = true;
        //     var cursorPos = textEdit.cursorRectangle;
        //     suggestionsView.x = cursorPos.x + 5;
        //     suggestionsView.y = cursorPos.y + 10;
        // }
    }
