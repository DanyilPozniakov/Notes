import QtQuick
import QtQuick.Controls

Window {
    width: 1000
    height: 600
    visible: true
    title: qsTr("Hello World")


    Item {
        id: noteEditor
        width: 500
        height: 250
        anchors.centerIn: parent
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
                textMargin: 10
                
                Keys.onPressed: (event) => {
                    var ch           = event.text
                    var completion   =  textHandler.completeBracket(ch)
                    if(completion){
                        event.accepted = true;
                        var cursor = textEdit.cursorPosition
                        textEdit.insert(textEdit.cursorPosition, ch);
                        textEdit.insert(textEdit.cursorPosition, completion);
                        textEdit.cursorPosition = cursor + 1;
                        return
                    }
                    else if(event.key === Qt.Key_Backspace) {
                        event.accepted = true;
                        var cursor      = textEdit.cursorPosition - 1;
                        var ch          = textEdit.text.charAt(cursor);
                        var posToDelete =  textHandler.deleteBracketPair(ch,textEdit.text.slice(cursor + 1));
                        if(posToDelete >= 0){
                            console.log(textEdit.text.slice(cursor + 1))
                            var absolutePathToDelete = cursor + posToDelete + 1
                            textEdit.remove(absolutePathToDelete ,absolutePathToDelete + 1)
                        }
                        textEdit.remove(cursor,cursor + 1)
                    }
                }
            }
        }
    }
}
