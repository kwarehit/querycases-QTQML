import QtQuick.Controls 2.2


ToolBar {
    id: background

    Label {
        id: label
        text: section
        anchors.fill: parent
        font.bold: true
        horizontalAlignment: Qt.AlignHCenter
        verticalAlignment: Qt.AlignVCenter
    }
}

