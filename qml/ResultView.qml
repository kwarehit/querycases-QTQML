import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

ScrollView{

    anchors.fill: parent

    property alias listView: listView

    ListView {
        id:listView

        model: resultModel

        delegate: ResultViewDelegate{
            width: listView.width
        }

        focus: true
        boundsBehavior: Flickable.StopAtBounds

        currentIndex:-1

        highlight: Rectangle {
            color: "lightgrey"
        }

        section.property: "casetype"
        section.criteria: ViewSection.FullString
        section.delegate: ResultViewSectionDelegate{
            width: listView.width
            height: 20
        }

        ScrollBar.vertical: ScrollBar { }

    }
}





