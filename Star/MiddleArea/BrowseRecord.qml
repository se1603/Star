import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

Rectangle {
    width: page_display.width
    height: page_display.height

    property var browseRecord: middleArea.middleface.browse_records

    ScrollView {
        anchors.fill: parent
        clip: true
        ColumnLayout {
            width: parent.width
            height: parent.height

            Text {
                id: browserecord_title
                text: " 历史记录"
                font.pixelSize: 23
                color: "#696969"
            }

            GridLayout {
                id: browserecord_grid
                anchors.top: browserecord_title.bottom
                anchors.topMargin: 15
                anchors.left: parent.left
                anchors.leftMargin: 15
                columns: mainWindow.width < 1100 ? 4 : 5
                columnSpacing: 15
                rowSpacing: 15
                Repeater {
                    model: browseRecord
                    Rectangle {
                        width: 200
                        height: 330
                        Rectangle {
                            id: browseRecord_img
                            width: parent.width
                            height: 290
                            Image {
                                width: parent.width
                                height: parent.height
                                source: "file:"+modelData.post
                            }
                        }
                        Text {
                            id: browseRecord_name
                            width: parent.width
                            text: modelData.name
                            wrapMode: Text.Wrap
                            anchors.top: browseRecord_img.bottom
                        }

                        Text {
                            id: browseRecord_info
                            text: modelData.startPlayTime+"   "+modelData.duration
                            anchors.top: browseRecord_name.bottom
                        }
                    }
                }
            }
            Text {
                id: notice
                text: "——暂时还没有任何观看记录——"
                font.pixelSize: 26
                color:"#696969"
                anchors.top: parent.top
                anchors.topMargin: 2 / 5 * page_display.height
                anchors.left: parent.left
                anchors.leftMargin: 1 / 3 * page_display.width
                visible:browseRecord[0].name === " " ? true : false
            }
        }
    }
}
