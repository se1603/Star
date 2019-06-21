import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Rectangle {
    width: page_display.width
    height: page_display.height

    property var myvariety:zongYi.varieties

    ScrollView {
            anchors.fill: parent
            clip: true
            ColumnLayout {
                width: parent.width
                height: parent.height

                Row{
                    id: row_menu
                    anchors.left:parent.left
                    spacing: 50
                    Repeater {
                        model:JSON.parse(client.showCategory(4))
                        delegate: categoryDelegate
                    }
                }

                GridLayout {
                    id: film_grid
                    anchors.top: collection_title.bottom
                    anchors.topMargin: 15
                    anchors.left: parent.left
                    anchors.leftMargin: 15
                    columns: page_display.width < 1000 ? 4 : 5
                    columnSpacing: page_display.width < 1000 ? 15 : 20
                    rowSpacing: 15
                    Repeater {
                        model: myvariety
                        Rectangle {
                            id:image
                            width: 220
                            height: 330
                            Image {
                                anchors.fill: parent
                                anchors.top: parent.top
                                source:"file:" + modelData.post
                            }
                            Rectangle {
                                id: filmname
                                width: parent.width
                                height: 30
                                anchors.bottom: parent.bottom
                            }
                            Text {
                                id: collection_text
                                width: parent.width
                                text: modelData.name
                                font.pixelSize: 15
                                wrapMode: Text.Wrap
                                anchors.top: filmname.top
                            }

                            MouseArea{
                                anchors.fill: parent
                                onClicked: {

                                    middleArea.duration = playInterface.playCommponent.player.showCurrentTime()

                                     middleArea.middle = false

                                    if(playInterface.playCommponent.playing)
                                    {
                                        playInterface.playCommponent.stopPlay()
                                        console.log("true")
                                    }

                                    play.datas = JSON.parse(client.getMovieInfo(modelData.name))

                                   middleArea.playRtspUrl = modelData.rtspURL
                                   play.esipode = Number(play.datas.resource.esipode)
                                   play.rtspUrl = modelData.rtspURL + "/1.mkv"

                                    play.visible = true
                                    play.name = modelData.name
                                    play.image = modelData.post


                                    //自动生成记录
                                    if(modelData.name !== middleArea.playingName
                                            && middleArea.playingName!==""){
                                        if(audienceInterface.audienceName === ""){
                                            client.addBrowseRecord(middleArea.playingName,middleArea.startTime,middleArea.duration,middleArea.videoType)
                                        }else{
                                            client.addRecord(audienceInterface.audienceName,middleArea.playingName,middleArea.startTime,middleArea.duration,middleArea.videoType)
                                        }
                                        middleArea.playingName = ""
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

    Component{
        id:categoryDelegate
        Rectangle {
            width: 50
            height : 40
            Text {
                id:category
                text: modelData.category
                opacity: 0.5
                font.pixelSize: 15
                color: 	"#808080"
                anchors.horizontalCenter: parent.horizontalCenter
                MouseArea {
                    anchors.fill: parent
                    acceptedButtons: Qt.RightButton | Qt.LeftButton
                    hoverEnabled: true
                    enabled: true

                    onEntered: {
                        parent.color = "#00BFFF"
                    }
                    onExited: {
                        parent.color = "#808080"
                    }
                    onClicked: {
                        if(category.text === "真人秀")
                            zongYi.varieties = JSON.parse(client.browseMovieAndTelevision(4,1))
                        else if(category.text == "选秀")
                            zongYi.varieties = JSON.parse(client.browseMovieAndTelevision(4,2))
                        else if(category.text == "美食")
                            zongYi.varieties = JSON.parse(client.browseMovieAndTelevision(4,3))
                        else if(category.text == "旅游")
                            zongYi.varieties = JSON.parse(client.browseMovieAndTelevision(4,4))
                        else if(category.text == "纪实")
                            zongYi.varieties = JSON.parse(client.browseMovieAndTelevision(4,5))
                        else if(category.text == "搞笑")
                            zongYi.varieties = JSON.parse(client.browseMovieAndTelevision(4,6))
                        else if(category.text == "访谈")
                            zongYi.varieties = JSON.parse(client.browseMovieAndTelevision(4,7))
                        load_page(category.text)
                    }
                }
            }
        }
    }

    function load_page(page){
        switch(page){
        case "推荐":
            variety_stack.push(recommend_variety,StackView.Immediate)
            break
        default:
            variety_stack.push(common_variety,StackView.Immediate)
            break
        }
    }
}
