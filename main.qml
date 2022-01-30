import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
import QtQml 2.2

import LogText 1.0
import Manager 1.0
import Model.ResultModel 1.0
import Model.ResultStatusItemModel 1.0
import Model.ResultModelItem 1.0

import "qml"


Window {
    id: root
    visible: true
    visibility: Window.Maximized
    title: qsTr("Query cases results")

    SplitView {
        anchors.fill: parent
        orientation: Qt.Horizontal

        SplitView
        {
            id:subview
            orientation: Qt.Vertical
            width:root.width/2

            QueryTextView{
                id:queryTextEdit
                height: subview.height/2
                Layout.fillWidth: true
            }

            Rectangle {
                id:rect1
                Layout.fillWidth: true

                ColumnLayout{
                    spacing: 2

                    LogTextView{
                        id:logTextEdit
                        Layout.preferredWidth: rect1.width
                        Layout.preferredHeight: 13*rect1.height/15
                    }

                    RowLayout{
                        spacing: 4
                        Layout.alignment: Qt.AlignLeft

                        Button {
                            id:queryButton
                            text: "query"
                            Layout.preferredHeight: 20

                            function enable(b){
                                enabled = b
                            }

                            onClicked: {
                                 manager.start()
                            }
                       }
                    }
                }
            }
        }

        Rectangle{
            id:rect
            height: root.height
            width: root.width/2

            ColumnLayout{
                spacing: 2

                Rectangle{
                    anchors.fill: parent
                    border.color: "lightgrey"

                    Layout.preferredWidth: rect.width
                    Layout.preferredHeight: 13*rect.height/14

                    ResultView{
                        id: resultView
                        clip: true
                    }
                }

                RowLayout{
                    spacing: 4

                    Layout.alignment: Qt.AlignRight

                    TextField{
                        id:findText
                        placeholderText: "Paste what case you want to find"
                        Layout.preferredWidth: 9*rect.width/10
                    }

                    Button {
                        id:findButton
                        text: "find"
                        Layout.preferredHeight: 20

                        onClicked: find(findText.text)

                        function find(str){

                            console.log(resultView.listView.model.rowCount())

                            for(var i = 0; i < resultView.listView.model.rowCount(); ++i){
                                var name = resultView.listView.model.getCaseName(i)
                                console.log(name)
                                if(name === str)
                                {
                                    console.log("find success: "+i)
                                    resultView.listView.currentIndex = i
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    property alias resultModel: resultModel
    property alias resultModelItem: resultModelItem

    ResultModel{
        id:resultModel
    }

    ResultModelItem{
        id:resultModelItem
    }


    property alias logtext: logtext
    property alias manager: manager

    LogText{
        id:logtext
    }

    Manager{
        id:manager
    }


    Component.onCompleted: {
        logtext.addLog.connect(logTextEdit.logTextEdit.logText)
        queryTextEdit.queryTextEdit.textChangedSignal.connect(manager.onQueryTextChanged)
        manager.setEnabledQueryButton.connect(queryButton.enable)
        resultModelItem.dateDone.connect(resultModel.onDataDone)
        resultModelItem.clearView.connect(resultModel.clear)
    }

}









