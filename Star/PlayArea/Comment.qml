//Author:徐丹
//time：2019.4.28
//节目界面

import QtQuick 2.0

Rectangle {
    id:commentPage
    property string name1:""
    property string types: ""
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
                source: "file:" + imge
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
                text: name1
                font.pixelSize: 10
            }
            Text{
                id:type
                text: types
                font.pixelSize: 10
            }
        }


    Row{
        id:row_icon
        anchors.top: image_re.bottom
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
        spacing: 10
        Image{
           id:dowm_img
           width: 30
           height: 30
           source: "qrc:/image/play/download.png"
        }
        Image{
            id:collect_img
            width: 30
            height: 30
            source: "qrc:/image/play/collect.jpg"
        }
        Image {
            id: share_img
            width: 30
            height: 30
            source: "qrc:/image/play/share.jpg"
        }
    }
    Rectangle{
        id:detailInfo
        width: 60
        height: 30
        anchors.top:image_re.bottom
        anchors.topMargin: 10
        anchors.left: row_icon.right
        anchors.right: parent.right
        Text{
            text: "detail"
            font.pixelSize: 16
        }
        MouseArea{
            anchors.fill: parent
            onClicked: {
                detail.visible = true
            }
        }
    }

    Rectangle{
        id:detail
//        visible: false
        border.color: "red"
        width: 200
        height: 200
        anchors.top: row_icon.bottom
        anchors.topMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 10
        Text{
            id:detailTe
            text: info
        }
    }
}
