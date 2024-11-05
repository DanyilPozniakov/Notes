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
                    const regex     = /^[A-Za-z0-9]$/;
                    const eventText = event.text;
                    const cursor    = textEdit.cursorPosition;
                    if (!regex.test(event.text)) {
                        event.accepted = textHandler.handleKeyPress(event.key,eventText,textEdit.text,cursor);
                    }
                }
                onTextChanged: {
                    const cursor    = textEdit.cursorPosition;
                    const pos       = textEdit.text.lastIndexOf(' ',cursor) + 1;
                    const word      = textEdit.text.slice(pos,cursor);
                    var sug         =  textHandler.autocompleteSuggestions(word);
                    if (sug) {
                        showSuggestions(sug);
                    }
                    else {
                        suggestionsView.visible = false;
                    }
                }
            }

            Rectangle {
                id: suggestionsView
                z: 5
                width: 150
                height: 75
                opacity: 0.4
                color: "white"
                border.width: 1
                border.color: "#aeb6bf"
                radius: 4
                visible: false

                ListView {
                    id: suggestionsViewList
                    anchors.fill: parent
                    model: textHandler.currentSuggestions
                    delegate: Text {
                        text: modelData
                        font.pixelSize: 12
                        color: "black"
                    }
                }
            }

            Connections{
                target: textHandler
                function onInsertText(cursorPos, text) {
                    var cursor = cursorPos === 0 ? textEdit.cursorPosition : cursorPos;
                    textEdit.insert(cursor,text);
                }
                function onUpdateCursorPosition(cursorPos) {
                    textEdit.cursorPosition = cursorPos;
                }
                function onDeleteText(start,end) {
                    textEdit.remove(start,end);
                }
            }
        }

        function showSuggestions(suggestions) {
            suggestionsView.visible = true;
            var cursorPos = textEdit.cursorRectangle;
            suggestionsView.x = cursorPos.x + 5;
            suggestionsView.y = cursorPos.y + 10;
        }
    }
