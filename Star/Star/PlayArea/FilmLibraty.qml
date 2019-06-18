//time:2019.4.30
//author:xudan
//内容：片库界面

import QtQuick 2.0
import QtQuick.Layouts 1.11

Rectangle{
    id:play_page
    width: left_stack.width
    height: left_stack.height

    color: "#424242"
    property string playname: ""
    property string playtype: ""
    property string img:""

    Text{
        id:te_play
        anchors.top:parent.top
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
        text: "正在播放"
        color: "white"
        font.pixelSize: 24
    }

    Row{
        id:row_play
        anchors.left: parent.left
        anchors.top: te_play.bottom
        anchors.topMargin: 10
        spacing: 5
        Rectangle{
            id:play_rec
            width: 2/5*play_page.width
            height: 1/5*play_page.height
             color: "red"
            Image{
                id:record_img
                width:parent.width
                height: parent.height
                source:"file:" + play.image
            }
        }
        Column{
            id:column_play
            anchors.left: row_play.right
            anchors.leftMargin: 5
            anchors.top: parent.top
            Text{
                id:name_te
                width: 3/5*play_page.width-30
                anchors.top: parent.top
                color: "white"
//                font.family: "Beta Dance"
                font.pixelSize: 14
                text: play.name
                wrapMode: Text.Wrap
            }
            Text{
                anchors.top:name_te.bottom
                //font.family: "Beta Dance"
                font.pixelSize: 14
                color: "white"
                text: play.datas.resource.esipode+"集全"
            }
        }
    }

    GridLayout{
        id:gird_play
        columns:10
        width: play_page.width
        anchors.top:row_play.bottom
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.right: parent.right
        Repeater{
            id:play_repeater
            model: play.datas.resource.esipode
            Rectangle{
                width: 15
                height: 15
                color: "red"
                Text{
                    anchors.centerIn: parent
                    text: modelData+1
                    color: "white"
                }
            }
        }
    }
}