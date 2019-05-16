//Author:徐丹
//time：2019.4.28
//节目界面

import QtQuick 2.0

Rectangle {
    id:commentPage
    property string name1:""

    property string info: ""
    property string imge:""

    width: /*59/60**/right_stack.width
    height: /*59/60**/right_stack.height


    color: "#8B8378"
    Rectangle{
        id:image_re
        anchors.top:parent.top
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 5
        width: 1/2*commentPage.width
        height: 1/4*commentPage.height
        color: "red"
        Image{
            id:com_img
            width: parent.width
            height: parent.height
            source: "file:" + play.image
        }
    }
    Column{
        spacing: 10
        anchors.top:parent.top
        anchors.topMargin: 10
        anchors.left: image_re.right
        anchors.leftMargin: 10
        Text{
            id:name
            text: play.name
            width: 1/2*commentPage.width-20
            font.pixelSize: 10
            wrapMode: Text.Wrap
        }
        Row{
            spacing: 5
            Repeater{
                model: play.datas.resource.videotype
                Text{
                    id:type
                    text: modelData.type
                    font.pixelSize: 10
                }
            }
        }

    }


    Row{
        id:row_icon
        anchors.top: image_re.bottom
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
        width: 100
        height: 30
        spacing: 5
        Image{
            id:dowm_img
            width: 25
            height: 30
            source: "qrc:/image/play/download.png"
        }
        Image{
            id:collect_img
            width: 25
            height: 30
            source: "qrc:/image/play/collect.jpg"
        }
        Image {
            id: share_img
            width: 25
            height: 30
            source: "qrc:/image/play/share.jpg"
        }

    }
    Rectangle{
        id:detailInfo
        width: 25
        height: 30
        anchors.top:image_re.bottom
        anchors.topMargin: 10
        anchors.left: row_icon.right
        anchors.right: parent.right
        anchors.rightMargin: 10
        Text{
            anchors.centerIn: parent
            text: "detail"
            font.pixelSize: 16
        }
        MouseArea{
            anchors.fill: parent
            onClicked: {
                console.log("pop.open")
                pop.open()
            }
        }
    }

    DetailPop{
        id:pop
    }
}
