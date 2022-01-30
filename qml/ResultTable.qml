import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3


TableView {
    model:resultModel.getSubModel(index)

//    style: TableViewStyle {
//        headerDelegate: Rectangle {
//            height: 20
//            color: "lightsteelblue"
//            Text {
//                anchors.centerIn: parent

//                //Layout.fillWidth: true
//                text: styleData.value
//                elide: Text.ElideMiddle
//            }
//        }
//    }

    itemDelegate: Item {

        Text {
            text: styleData.value
            elide: Text.ElideRight
            onLinkActivated: Qt.openUrlExternally(link)
        }
    }

    TableViewColumn {
        title: "CodeLine"
        role: "casecodeline"
    }

    TableViewColumn {
        title: "Result"
        role: "caseresult"
    }

    TableViewColumn{
        title:"Time"
        role:"casetime"
    }

    TableViewColumn{
        title:"Details"
        role:"casedet"
    }

    TableViewColumn{
        title:"TestSequence"
        role:"caseseq"
    }

    TableViewColumn{
        title:"Machine"
        role:"casemachine"
    }
}
