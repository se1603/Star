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
        model: la//play.datas
        delegate: dele
    }

    ListModel{
        id:la
        ListElement{
           it:"jjjj"
        }
        ListElement{
           it:"jjjj"
        }
        ListElement{
           it:"jjjj"
        }
        ListElement{
           it:"jjjj"
        }
    }

    Component{
        id:dele
        Rectangle{
            width: all_scroll.width
            height: 200
            border.color: "#dddddd"
            Rectangle{
                id:all_message
                anchors.top: parent.top
                width: parent.width*2/3
                height: parent.height-10
                color: "#55ddaa"
//                Image{
//                    anchors.fill: parent
//                    source: modelData.post
//                }
            }
            Text{
                id:all_time
                anchors.top: parent.top
                anchors.left: all_message.right
                text: "dgdg"//modelData.name
                font.pixelSize: 26
                width: 1/3*parent.width
                wrapMode: Text.Wrap
            }
        }
    }
}
