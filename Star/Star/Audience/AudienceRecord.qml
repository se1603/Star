import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2

Rectangle {
    width: 59 / 60 * audienceDisplay.width
    height: 59 / 60 * audienceDisplay.height
    border.color: "gray"

    property var record:audience.videos

    ScrollView {
        anchors.fill: parent
        clip: true
        ColumnLayout {
            width: parent.width
            height: parent.height

            Text {
                id: record_title
                text: " 历史记录"
                font.pixelSize: 20
                opacity: 0.7
            }
            GridLayout {
                id: record_grid
                anchors.top: record_title.bottom
                anchors.topMargin: 15
                anchors.left: parent.left
                anchors.leftMargin: 15
                columns: mainWindow.width < 1100 ? 4 : 5
                columnSpacing: 15
                rowSpacing: 15
                Repeater {
                    model: record
                    Rectangle {
                        width: 200
                        height: 330
                        Rectangle {
                            id: record_img
                            width: parent.width
                            height: 290
                            Image {
                                width: parent.width
                                height: parent.height
                                source: "file:"+modelData.post
                            }
                        }
                        Text {
                            id: record_name
                            width: parent.width
                            text: modelData.name
                            wrapMode: Text.Wrap
                            anchors.top: record_img.bottom
                        }
                        Text {
                            id: record_info
                            text: modelData.startPlayTime+"   "+modelData.duration
                            anchors.top: record_name.bottom
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
                visible:record[0].name === " " ? true : false
            }
        }
    }
}
