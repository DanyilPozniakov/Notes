import QtQuick
import QtQuick.Controls

Item {
        id: noteEditor
        Rectangle{
            anchors.fill: parent
            border.width: 1
            border.color: "#aeb6bf"
            radius: 4
            color: "#d6dbdf"

            TextEdit{
                id: textEdit
                anchors.fill: parent
                wrapMode: TextEdit.Wrap
                font.family: "JetBrains Mono"
                textMargin: 10

                Keys.onPressed: (event) => {
                    const regex = /^[A-Za-z0-9]$/;
                    const key = event.key;
                    const eventText = event.text;
                    const cursor = textEdit.cursorPosition;
                    if (!regex.test(event.text)) {
                        console.log("else");
                        event.accepted = textHandler.handleKeyPress(event.key,eventText,textEdit.text,cursor);
                    }
                }
            }

            Connections{
                target: textHandler
                function onInsertText(cursorPos, text) {
                    textEdit.insert(textEdit.cursorPosition,text);
                }
                function onUpdateCursorPosition(cursorPos) {
                    textEdit.cursorPosition = cursorPos;
                }
                function onDeleteText(start,end) {
                    textEdit.remove(start,end);
                }
            }
        }
    }
