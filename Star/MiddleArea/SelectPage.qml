//Author:徐丹
//time：2019.5.5
//内容：精选内容展示
//修改：点击post跳转到播放界面

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

                        }
                    }
                }
            }

            ListView{
                id: slide_films
                width: parent.width
                height: 4/15 * parent.height
                anchors.left: slide_row.right
                anchors.top:slide_row.top
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
                            spacing: mainWindow.width < 1200 ? 15 : 50
                            Repeater {
                                model: modelData.films
                                Rectangle {
                                    width:  mainWindow.width < 1200 ? 175 : 197
                                    height:  page_display.width < 1000 ? 290 : 326
                                    Rectangle {
                                        id: collection_img
                                        width: parent.width
                                        height:  page_display.width < 1000 ? 263 : 296
                                        color: "red"

                                        Image {
                                            anchors.fill: parent
                                            anchors.top: parent.top
                                            source:"file:" + modelData.post
                                        }

                                        MouseArea{
                                            anchors.fill: parent
                                            onClicked: {
                                                play.visible = true
                                                play.name = modelData.name
                                                play.image = modelData.post
                                                play.datas = JSON.parse(client.getMovieInfo(modelData.name,0))
                                                console.log(play.datas.resource.videotype.type)
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
