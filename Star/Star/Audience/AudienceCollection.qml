import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import "../MiddleArea"

Rectangle {
    width: 59 / 60 * audienceDisplay.width
    height: 59 / 60 * audienceDisplay.height
    border.color: "gray"

    property var collection:audience.videos

    ScrollView {
        anchors.fill: parent
        clip: true
        ColumnLayout {
            width: parent.width
            height: parent.height

            Text {
                id: collection_title
                text: " 我的收藏"
                font.pixelSize: 20
                opacity: 0.7
            }
            GridLayout {
                id: collection_grid
                anchors.top: collection_title.bottom
                anchors.topMargin: 15
                anchors.left: parent.left
                anchors.leftMargin: 15
                columns: mainWindow.width < 1100 ? 4 : 5
                columnSpacing: 15
                rowSpacing: 15

                Repeater {
                    model: collection
                    Rectangle {
                        width: 200
                        height: 330
                        Rectangle {
                            id: collection_img
                            width: parent.width
                            height: 290
                            Image {
                                width: parent.width
                                height: parent.height
                                source: "file:"+modelData.post
                                MouseArea{
                                    anchors.fill:parent
                                    onClicked: {

                                    }
                                }
                            }
                        }
                        Text {
                            id: collection_name
                            width: parent.width
                            text: modelData.name
                            wrapMode: Text.Wrap
                            anchors.top: collection_img.bottom
                        }
                        Text {
                            id: collection_time
                            text: modelData.collecttime
                            anchors.top: collection_name.bottom
                        }
                    }
                }
            }
            Text {
                id: notice
                text: "——这里空空如也——"
                font.pixelSize: 26
                color:"#696969"
                anchors.left: parent.left
                anchors.leftMargin: 1 / 3 * audienceDisplay.width
                visible:collection[0].name === " " ? true : false
            }
        }
    }
}
