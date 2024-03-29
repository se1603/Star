import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Rectangle {
    id:comic_recommend
    width: page_display.width
    height: page_display.height

    property var recommendComics:JSON.parse(client.showRecommend(3))
    //        ["正在热播","热门华语大片","高人气好莱坞大片","经典高分港片","历年贺岁大片精选"]

//    property var films: ["1","2","3","4","5"]

    ScrollView{
        anchors.fill: parent
        clip: true
        ColumnLayout{
            width: parent.width
            height: parent.height

            Row{
                id: row_comic_menu
                anchors.left:parent.left
                spacing: 50
                Repeater {
                    model:JSON.parse(client.showCategory(3))
                    delegate: category_comic_dele
                }
            }

            Row{
                id:row_image_comic
                Rectangle{
                    id:slide_comic_image
                    width: comic_recommend.width
                    height: mainWindow.width < 1200 ? 342 : 442
                    color: "red"
                    Image {
                        id: film_comic_image
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
                id: slide_comic
                width:  mainWindow.width < 1200 ? 1000 : 1200
                height: 40
                opacity: 0.8
                anchors.top: row_image_comic.top
                anchors.left: row_image_comic.left
                anchors.right: row_image_comic.right
                anchors.topMargin: mainWindow.width < 1200 ? 302 : 404
                orientation: ListView.Horizontal
                z:5
                model:recommendComics.firstRecommends
                delegate: show_comic_slide
            }

            ColumnLayout{
                anchors.top:slide_comic_image.bottom
                anchors.topMargin: 20
                spacing: page_display.width < 1000 ? 10 : 60

                Repeater{
                    id:show_comic_film
                    model:recommendComics.secondRecommends.resource
                    Rectangle{
                        width: page_display.width
                        height: page_display.width < 1000 ? 355 : 400
                        Text {
                            id:comic_title
                            text: modelData.title
                            font.pixelSize: 24
                        }

                        Row {
                            id: comic_grid
                            anchors.top: comic_title.bottom
                            anchors.topMargin: 15
                            anchors.left: parent.left
                            spacing: mainWindow.width < 1200 ? 15 : 50
                            Repeater {
                                model: modelData.films
                                Rectangle {
//                                    width:  mainWindow.width < 1200 ? 175 :225
//                                    height:  page_display.width < 1000 ? 290 : 370
                                    width:  mainWindow.width < 1200 ? 175 : 197
                                    height:  page_display.width < 1000 ? 290 : 326
                                    Rectangle {
                                        id: collectiob_img_comic
                                        width: parent.width
//                                          height:  page_display.width < 1000 ? 263 : 340
                                        height:  page_display.width < 1000 ? 263 : 296
                                        Image {
                                            anchors.fill: parent
                                            anchors.top: parent.top
                                            source:"file:" + modelData.post
                                        }

                                        MouseArea{
                                            anchors.fill: parent
                                            onClicked: {
                                                middleArea.duration = playInterface.playCommponent.player.showCurrentTime()
                                            console.log(modelData.post)


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
                                        id: collectiob_text_comic
                                        width: parent.width
                                        text: modelData.name
                                        wrapMode: Text.Wrap
                                        anchors.top: collectiob_img_comic.bottom
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
        id:time_comic
        interval: 3000
        running: true
        repeat: true
        onTriggered:{
            if(slide_comic.currentIndex ===  4)
            {
                slide_comic.currentIndex -= 4

            }else{
                slide_comic.currentIndex += 1
            }
        }
    }

    Component{
        id:category_comic_dele
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
                        if(category.text === "机战")
                            comic.comics = JSON.parse(client.browseMovieAndTelevision(3,1))
                        else if(category.text == "青春")
                            comic.comics = JSON.parse(client.browseMovieAndTelevision(3,2))
                        else if(category.text == "格斗")
                            comic.comics = JSON.parse(client.browseMovieAndTelevision(3,3))
                        else if(category.text == "恋爱")
                            comic.comics = JSON.parse(client.browseMovieAndTelevision(3,4))
                        else if(category.text == "美少女")
                            comic.comics = JSON.parse(client.browseMovieAndTelevision(3,5))
                        else if(category.text == "热血")
                            comic.comics = JSON.parse(client.browseMovieAndTelevision(3,6))
                        else
                            comic.comics = JSON.parse(client.browseMovieAndTelevision(3,7))

                        load_comic_page(category.text)
                    }
                }
            }
        }
    }

    Component{
        id:show_comic_slide
        Rectangle{
            id: slideRect_comic
            height: 40
            width: row_image_comic.width/5
            color:ListView.isCurrentItem ? "lightblue" : "white"
            onColorChanged: {
                film_comic_image.source = "file:" + modelData.post
            }
            Text {
                id: slideComic_name
                text: modelData.name
                anchors.centerIn: parent
                color: "black"
            }

            MouseArea {
                id:mousearea1
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
                    if(slideRect_comic.ListView.view.currentIndex !== index){
                        slideRect_comic.ListView.view.currentIndex = index;
                    }
                    time_comic.stop()
                }
                onExited: {
                    time_comic.restart()
                }
            }
        }
    }

    function load_comic_page(page){
        switch(page){
        case "推荐":
            comic_stack.push(comicRecommend_page,StackView.Immediate)
            break
        default:
            comic_stack.push(comictype_page,StackView.Immediate)
            break
        }
    }
}

