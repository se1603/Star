//Author:徐丹
//time：2019.4.28
//节目界面

import QtQuick 2.0
import QtQuick.Controls 2.2

Rectangle {
    id:commentPage
    property string name1:""

    property string info: ""
    property string imge:""


    property var date:new Date()
    property var collections

    width: /*59/60**/right_stack.width
    height: /*59/60**/right_stack.height


    color: "#424242"
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
            color: "white"
        }
        Text{
            id:region
            text: play.datas.resource.region
            color: "white"
        }
        Row{
            spacing: 5
            Repeater{
                model: play.datas.resource.videotype
                Text{
                    id:type
                    text: modelData.type
                    font.pixelSize: 10
                    color: "white"
                }
            }
        }
        Text {
            id: notice
//            text: play.datas.resource.ca// "hhhhhhhhhh"
            font.pixelSize: 12
            color: "#ffffff"
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
            source: "qrc:/image/play/collect.png"
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    var year = date.getFullYear()
                    var month = date.getMonth()+1
                    var day = date.getDate()
                    var hours = date.getHours()
                    var minutes = date.getMinutes()
                    var collecttime = year+"-"+month+"-"+day+"-"+hours+":"+minutes
                    if(audienceInterface.audienceName === ""){
                        audienceItem.open()
                    }else{
                        search(play.name,collecttime)
                    }
                }
            }
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
            text: "详情"
//            text: "detail"
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

    onVisibleChanged: {
        notice.text = ""
    }

    Connections{
        target: client
        onCollectsucceed: {
            audienceInterface.videos = JSON.parse(client.audienceCollection(audienceInterface.audienceName))
        }
        onCollectfailed: {
        }
    }

    function search(cName,collecttime){
        var flag = 0
        collections = JSON.parse(client.audienceCollection(audienceInterface.audienceName))
        for(var i=0;i<collections.length;i++){
            if(cName === collections[i].name){
                notice.text = "已经收藏过了"
                flag = 1
            }
        }

        if(flag === 0){
            notice.text = "正在收藏..."
            client.addCollection(audienceInterface.audienceName,
                                 collecttime,play.name,play.datas.resource.category)
        }
    }
}
