/*
  Author:王梦娟
  Date: 2019-5-1 电影显示
*/
import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Rectangle {
    width: page_display.width
    height: page_display.height
    //    color: "yellow"
    property var films: movie.films

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
                    model:JSON.parse(client.showCategory(1))
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
                    model: films
                    Rectangle {
                        id:image
                        width: 220
                        height: 330
                        //                            border.color: "red"
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
                            //                                border.color : "green"
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
                                middleArea.middle = false
                                middleArea.duration = playInterface.playCommponent.player.showCurrentTime()
                                if(playInterface.playCommponent.playing)
                                {
                                    playInterface.playCommponent.stopPlay()
                                    console.log("true")
                                }

                                play.rtspUrl = modelData.rtspURL + ".mkv"


                                play.visible = true
                                play.name = modelData.name
                                play.image = modelData.post

                                play.datas = JSON.parse(client.getMovieInfo(modelData.name))
                                //                                    play.commentModel = JSON.parse(client.showCommentInfo(play.name))
                                console.log(play.datas.resource.videotype.type)

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
                        if(category.text === "武侠")
                            movie.films = JSON.parse(client.browseMovieAndTelevision(1,1))
                        else if(category.text == "悬疑")
                            movie.films = JSON.parse(client.browseMovieAndTelevision(1,2))
                        else if(category.text == "喜剧")
                            movie.films = JSON.parse(client.browseMovieAndTelevision(1,3))
                        else if(category.text == "动作")
                            movie.films = JSON.parse(client.browseMovieAndTelevision(1,4))
                        else if(category.text == "爱情")
                            movie.films = JSON.parse(client.browseMovieAndTelevision(1,5))
                        else if(category.text == "动画")
                            movie.films = JSON.parse(client.browseMovieAndTelevision(1,6))
                        else if(category.text == "惊悚")
                            movie.films = JSON.parse(client.browseMovieAndTelevision(1,7))
                        else
                            movie.films = JSON.parse(client.browseMovieAndTelevision(1,8))
                        load_page(category.text)
                    }
                }
            }
        }
    }

    function load_page(page){
        switch(page){
        case "推荐":
            film_stack.push(recommend_film,StackView.Immediate)
            break
        default:
            film_stack.push(common_film,StackView.Immediate)
            break
        }
    }
}
