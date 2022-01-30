import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2


Rectangle {

    property alias logTextEdit: logTextEdit

    color: "lightgray"

    ScrollView {
        anchors.fill: parent

        TextArea{
            id:logTextEdit
            readOnly: true
            text: manager.getTutorials()
            activeFocusOnPress:false
            anchors.fill: parent

            function logText(s){
                logTextEdit.insert(logTextEdit.length, s)
                logTextEdit.cursorPosition = text.length
            }
        }
    }
}



