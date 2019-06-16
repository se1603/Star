//Author:徐丹
//time：2019.4.28
//全部评论界面

import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2

ScrollView{
    anchors.fill: parent
    id:all_scroll
    clip: true
    property alias model:listview.model

    ListView{
        id:listview
        anchors.fill: parent
        model: la
        delegate: dele
    }

    Component{
        id:dele
        Rectangle{
            width: all_scroll.width
            height: 100
            border.color: "#dddddd"

            CommentPop{
                id:dd
            }
            Text{
                id:all_name
                anchors.top:parent.top
                anchors.left: parent.left
                text: name//te
                color: "blue"
            }
            Rectangle{
                id:all_message
                anchors.top: all_name.bottom
                width: parent.width
                height: parent.height/2
                border.color: "#55ddaa"
                Text{
                    id:all_te
                    width: parent.width-10
                    //            height: 60
                    anchors.top: parent.top
                    anchors.topMargin: 2
                    font.family: "Beta Dance"
                    font.pixelSize: 18
                    text:message//"message ddf dfs sf sf eef ss"
                    wrapMode: Text.Wrap
                }
            }
            Text{
                id:all_time
                anchors.top: all_message.bottom
                anchors.left: parent.left
                text: time//"dfa"
                font.pixelSize: 18
            }
            Rectangle{
                id:all_reply
                anchors.top:all_message.bottom
                anchors.left: all_time.right
                anchors.leftMargin: 90
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
                        onClicked: dd.open()
//                        list.insert(0,{name:"ff",message:"text",time:"3.1"})
                       //list.append({name:"ff",message:"text",time:"3.1"})
                    }
                }
            }

        }
    }
}
