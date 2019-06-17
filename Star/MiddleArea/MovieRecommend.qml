/*
  Author:王梦娟
  Date: 2019-5-1 电影显示
*/
import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Rectangle {
    id:recommend
    width: page_display.width
    height: page_display.height

    property var recommendFilms:JSON.parse(client.showRecommend(1))
    //        ["正在热播","热门华语大片","高人气好莱坞大片","经典高分港片","历年贺岁大片精选"]

    property var films: ["1","2","3","4","5"]

    ScrollView{
        anchors.fill: parent
        clip: true
        ColumnLayout{
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

            Row{
                id:row_image
                Rectangle{
                    id:slideImage
                    width: mainWindow.width < 1200 ? 702 : 950
                    height: mainWindow.width < 1200 ? 342 : 442
                    color: "red"
                    Image {
                        id: film_image
                        anchors.fill: parent
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            //                            aaa.text = recommendTitle
                            //                            console.log(recommendTitle)
                        }
                    }
                }
            }

            ListView{
                id: slide_films
                width: parent.width
                height: 4/15 * parent.height
                anchors.left: row_image.right
                anchors.top:row_image.top
                model:recommendFilms.firstRecommends
                delegate: show_slide
            }

            ColumnLayout{
                anchors.top:slideImage.bottom
                anchors.topMargin: 20
                spacing: page_display.width < 1000 ? 10 : 60

                Repeater{
                    id:show_film
                    model:recommendFilms.secondRecommends.resource
                    Rectangle{
                        width: page_display.width
                        height: page_display.width < 1000 ? 355 : 400
//                        color: "yellow"
                        Text {
                            id:recommend_title
                            text: modelData.title
                            font.pixelSize: 24
                        }

                        Row {
                            id: film_grid
                            anchors.top: recommend_title.bottom
                            anchors.topMargin: 15
                            anchors.left: parent.left
                            spacing: mainWindow.width < 1200 ? 15 : 50
                            Repeater {
                                model: modelData.films
                                Rectangle {
                                    width:  mainWindow.width < 1200 ? 175 : 197
                                    height:  page_display.width < 1000 ? 290 : 326
//                                    border.color: "red"
                                    Rectangle {
                                        id: collection_img
                                        width: parent.width
                                        height:  page_display.width < 1000 ? 263 : 296
//                                        border.color : "green"
                                        Image {
                                            anchors.fill: parent
                                            anchors.top: parent.top
                                            source:"file:" + modelData.post
                                        }

                                        MouseArea{
                                            anchors.fill: parent
                                            onClicked: {
                                                middleArea.duration = playInterface.playCommponent.player.showCurrentTime()
                                                if(playInterface.playCommponent.playing)
                                                {
                                                    playInterface.playCommponent.stopPlay()
                                                    console.log("true")
                                                }

                                                play.rtspUrl = modelData.rtspURL

                                                play.visible = true
                                                play.name = modelData.name
                                                play.image = modelData.post
                                                play.datas = JSON.parse(client.getMovieInfo(modelData.name))
//                                                play.commentModel = JSON.parse(client.showCommentInfo(play.name))
                                                console.log(play.datas.resource.videotype.type)

                                                if(modelData.name !== middleArea.playingName
                                                        && middleArea.playingName!==""){
                                                    client.addRecord(audienceInterface.audienceName,middleArea.playingName,middleArea.startTime,middleArea.duration,middleArea.videoType)
                                                    middleArea.playingName = ""
                                                }
                                            }
                                        }
                                    }
                                    Text {
                                        id: collection_text
                                        width: parent.width
                                        text: modelData.name
                                        wrapMode: Text.Wrap
                                        anchors.top: collection_img.bottom
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    Timer {
        id:time
        interval: 3000
        running: true
        repeat: true
        onTriggered:{
            if(slide_films.currentIndex ===  4)
            {
                slide_films.currentIndex -= 4

            }else{
                slide_films.currentIndex += 1
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

    Component{
        id:show_slide
        Rectangle{
            id: slideRect
            width: 250
            height: slideImage.height / 5
            color:ListView.isCurrentItem ? "lightblue" : "white"
            onColorChanged: {
                film_image.source = "file:" + modelData.post
            }
            Text {
                id: slideFilm_name
                text: modelData.name
                anchors.centerIn: parent
                color: "black"
            }

            MouseArea {
                id:mousearea
                acceptedButtons: Qt.RightButton | Qt.LeftButton
                hoverEnabled: true
                propagateComposedEvents: true
                enabled: true
                anchors.fill: parent

                onClicked: {
                    //                    play.visible = true
                    //                    play.thename = rect.moviename
                    //                    play.thesource = rect.movieurl
                    console.log(parent.width)
                }

                onEntered: {
                    //鼠标覆盖，显示对应的图片
                    if(slideRect.ListView.view.currentIndex !== index){
                        slideRect.ListView.view.currentIndex = index;
                    }
                    time.stop()
                }
                onExited: {
                    time.restart()

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
