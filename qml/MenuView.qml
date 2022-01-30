import QtQuick 2.7
import QtQuick.Controls 2.2



Item{

    property alias mainMeun : mainMenu

    Menu{
        id: mainMenu

        width: 45
        height: 20


        MenuItem{
            id: pasteItem
            text: "Paste"
            height: 20

            Shortcut{
                sequence: StandardKey.Paste
            }

            onTriggered: {
                queryTextEdit.paste()
            }
        }
    }


}
