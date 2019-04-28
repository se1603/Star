import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2


ScrollView{
    anchors.fill: parent
    id:all_scroll
    clip: true
    property alias model:listview.model
//    property  name: value

    ListView{
        id:listview
        anchors.fill: parent
        model: la
        delegate: dele
    }

    ListModel{
        id:la
        ListElement{
            te:"1"
        }
        ListElement{
            te:"2"
        }
        ListElement{
            te:"3"
        }
        ListElement{
            te:"4"
        }
        ListElement{
            te:"5"
        }
        ListElement{
            te:"6"
        }
        ListElement{
            te:"7"
        }
        ListElement{
            te:"8"
        }
    }

    Component{
        id:dele
        Rectangle{
            width: all_scroll.width
            height: 100
            border.color: "#dddddd"
            Text{
                id:all_name
                anchors.top:parent.top
                anchors.left: parent.left
                text: te
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
                    text:"message ddf dfs sf sf eef ss"
                    wrapMode: Text.Wrap
                }
            }
            Text{
                id:all_time
                anchors.top: all_message.bottom
                anchors.left: parent.left
                text: "dfa"
                font.pixelSize: 18
            }
            Rectangle{
                id:all_reply
                anchors.top:all_message.bottom
                anchors.left: all_time.right
                anchors.leftMargin: 50
                width: 50
                height: 30
                Text{
                    font.family: "Beta Dance"
                    font.pixelSize: 18
                    anchors.fill: parent
                    text: "回复"
                }
            }
        }
    }


}

