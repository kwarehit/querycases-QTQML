import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2



            
Rectangle {

    property alias queryTextEdit: queryTextEdit

    //color: "lightgrey"

    ScrollView {
        anchors.fill: parent

        TextArea{
            id:queryTextEdit

            focus: true
            selectByMouse: true
            selectByKeyboard: true
            wrapMode: TextEdit.wrap
            persistentSelection: true

            placeholderText : "Please paste what cases you want to query as example format"
            text : manager.getOneExample()

            anchors.fill: parent

            background: Rectangle {
                border.color: "lightgrey"
            }

            signal textChangedSignal(string s)

            onTextChanged: {
                textChangedSignal(text)
            }

            MouseArea{
                anchors.fill: parent
                acceptedButtons: Qt.RightButton

                onClicked: {
                    if(mouse.button == Qt.RightButton){
                        menuView.mainMeun.x = mouse.x
                        menuView.mainMeun.y = mouse.y
                        menuView.mainMeun.open()
                    }

                }
            }

            MenuView{
                id: menuView
            }
        }
    }
}
