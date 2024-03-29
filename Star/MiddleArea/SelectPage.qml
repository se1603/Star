import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Rectangle {
    id:selectPage
    width: page_display.width
    height: page_display.height

    property var recommendFilms:JSON.parse(client.showRecommend(0))

    ScrollView{
        anchors.fill: parent
        clip: true
        ColumnLayout{
            width: parent.width
            height: parent.height

            Row{
                id:slide_row
                Rectangle{
                    id:slideImage
                    height: mainWindow.width < 1200 ? 342 : 442
                    width: selectPage.width
                    color: "red"
                    Image {
                        id: film_image
                        anchors.fill: parent
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            console.log(film_image.source)
                        }
                    }
                }
            }

            ListView{
                id: slide_films
                width:  mainWindow.width < 1200 ? 1000 : 1200
                height: 40
                opacity: 0.8
                anchors.top: slide_row.top
                anchors.left: slide_row.left
                anchors.right: slide_row.right
                anchors.topMargin: mainWindow.width < 1200 ? 302 : 404
                orientation: ListView.Horizontal
                z:5
                model:recommendFilms.firstRecommends
                delegate: show_slide
            }

            ColumnLayout{
                anchors.top:slide_row.bottom
                anchors.topMargin: 20
                spacing: page_display.width < 1000 ? 10 : 60

                Repeater{
                    id:show_film
                    model:recommendFilms.secondRecommends.resource
                    Rectangle{
                        //                        color: "green"
                        width: page_display.width
                        height: page_display.width < 1000 ? 355 : 400
                        //                        color: "red"
                        Text {
                            id:recommend_title
                            text:  modelData.title
                            font.pixelSize: 24
                        }

                        Row {
                            id: film_grid
                            anchors.top: recommend_title.bottom
                            anchors.topMargin: 15
                            anchors.left: parent.left
                            spacing: mainWindow.width < 1200 ? 15 : 25
                            Repeater {
                                model: modelData.films
                                Rectangle {
                                    width: mainWindow.width < 1200 ? 175 : 197
                                    height: page_display.width < 1000 ? 290 : 326
                                    //                                    width:  mainWindow.width < 1200 ? 175 :(mainWindow.width > 1400 ? 240 : 225)
                                    //                                    height:  page_display.width < 1000 ? 290 : 326
                                    //                                    color: "green"
                                    Rectangle {
                                        id: collection_img
                                        width: parent.width
                                        height:  page_display.width < 1000 ? 263 : 296
                                        //                                        color: "red"
                                        Image {
                                            id:showPost
                                            anchors.fill: parent
                                            anchors.top: parent.top
                                            source:"file:" + modelData.post
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
                                                play.rtspUrl = modelData.rtspURL + ".mkv"

                                                if(play.datas.resource.esipode !== "1")
                                                {
                                                    play.rtspUrl = modelData.rtspURL + "/1.mkv";
                                                }

                                                play.visible = true
                                                play.name = modelData.name
                                                console.log("select"+play.name)
                                                play.image = modelData.post

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
        id:show_slide
        Rectangle{
            id: slideRect
            height: 40
            width: slide_row.width/5
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
}
