//Author:徐丹
//time：2019.4.28
//全部评论界面

import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2

ScrollView{
    anchors.fill: parent
    id:all_scroll
    background: Rectangle{
        anchors.fill: parent
        color: "#8B8378"
    }

    clip: true
    property var models
    property bool listFlag: false

//    property var vect:JSON.parse(client.showCommentInfo(play.name))
    Rectangle{
        width: parent.width
        height: 100
        color: "#8B8378"
        visible: listFlag ? false : true
        Text{
            text: "暂无评论"
            font.pixelSize: 24
            anchors.centerIn: parent
        }
    }

    ListView{
        id:listview
        anchors.fill: parent
        model:models
        delegate: dele
    }


    Component{
        id:dele
        Rectangle{
            width: all_scroll.width
            height: 100
            border.color: "#dddddd"
            color: "#8B8378"

            CommentPop{
                id:dd
            }
            Text{
                id:all_name
                anchors.top:parent.top
                anchors.left: parent.left
                text:modelData.audienceName
                color: "blue"
            }
            Rectangle{
                id:all_message
                anchors.top: all_name.bottom
                width: parent.width
                height: parent.height/2
                border.color: "#55ddaa"
                color: "#8B8378"

                Text{
                    id:all_te
                    width: parent.width-10
                    anchors.top: parent.top
                    anchors.topMargin: 2
                    anchors.left: parent.left
                    anchors.leftMargin: 2
                    font.family: "Beta Dance"
                    font.pixelSize: 18
                    text: modelData.comment
                    wrapMode: Text.Wrap
                }
            }
            Text{
                id:all_time
                anchors.top: all_message.bottom
                anchors.left: parent.left
                text:modelData.time
                font.pixelSize: 10
            }
            Rectangle{
                id:all_reply
                anchors.top:all_message.bottom
                anchors.right: parent.right
                anchors.rightMargin: 18

                width: 50
                height: 30
                color: "blue"


                Text{
                    font.family: "Beta Dance"
                    font.pixelSize: 18
                    anchors.fill: parent
                    text: "回复"
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        if(audienceInterface.audienceName == ""){
                            audienceItem.open()
                        }else{
                            dd.open()
                        }
                    }
                }
            }
        }
    }
}
