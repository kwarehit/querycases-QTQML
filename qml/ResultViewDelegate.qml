import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import QtQuick.Controls 2.2



ItemDelegate {
    id:delegate
    checkable: true

    contentItem: ColumnLayout {
        spacing: 10

        Label {
            text: casename
            font.bold: true
            elide: Text.ElideRight
            Layout.fillWidth: true
            ToolTip.visible: hovered
            ToolTip.delay: 1000
            ToolTip.timeout: 5000
            ToolTip.text: casename
        }


        GridLayout {
            id: grid
            visible: false

            ResultTable{
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
        }
    }

    states: [
        State {
            name: "expanded"
            when: delegate.checked

            PropertyChanges {
                target: grid
                visible: true
            }
        }
    ]

    onClicked: listView.currentIndex = index
}
