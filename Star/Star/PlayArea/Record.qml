import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2

ScrollView{
    anchors.fill: parent
    id:all_scroll
    clip: true

    property var records:JSON.parse(client.browseRecord())

    ListView{
        id:listview
        anchors.fill: parent
        model: records
        delegate: dele
    }

    Component{
        id:dele
        Rectangle{
            width: all_scroll.width
            height: 200
            Rectangle{
                id: all_message
                anchors.top: parent.top
                width: parent.width*2/3
                height: parent.height-10
                Image {
                    width: parent.width
                    height: parent.height
                    source: "file:"+modelData.post
                }
            }
            Text{
                id:all_time
                anchors.top: parent.top
                anchors.left: all_message.right
                text: modelData.name
                font.pixelSize: 16
                color: "#696969"
                width: 1/3 * parent.width
                wrapMode: Text.Wrap
            }
        }
    }
}
