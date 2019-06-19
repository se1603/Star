/*author:古长蓉
 *Data：2019-05-13
 *显示剧集推荐页面
 */
import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Rectangle{
    id:drame
    width: page_display.width
    height: page_display.height

    property var recommendDrames: JSON.parse(client.showRecommend(2))
    property var drames: ["1", "2", "3", "4", "5"]  //["正在热播","猜你喜欢","排行榜","卫视同步","偶像剧场"]

    ScrollView{
        anchors.fill: parent
        clip: true
        ColumnLayout{
            width: parent.width
            height: parent.height

            Row{
                id: row_drame_menu
                anchors.left:parent.left
                spacing: 50
                Repeater {
                    model:JSON.parse(client.showCategory(2))
                    delegate: category_drame_dele
                }
            }

            Component{
                id:category_drame_dele
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
                                if(category.text === "古装")
                                    drame.drames = JSON.parse(client.browseMovieAndTelevision(2,1))
                                else if(category.text === "悬疑")
                                    drame.drames = JSON.parse(client.browseMovieAndTelevision(2,2))
                                else if(category.text === "武侠")
                                    drame.drames = JSON.parse(client.browseMovieAndTelevision(2,3))
                                else if(category.text === "都市")
                                    drame.drames = JSON.parse(client.browseMovieAndTelevision(2,4))
                                else if(category.text === "历史")
                                    drame.drames = JSON.parse(client.browseMovieAndTelevision(2,5))
                                else if(category.text === "偶像")
                                    drame.drames = JSON.parse(client.browseMovieAndTelevision(2,6))
                                else if(category.text === "家庭")
                                    drame.drames = JSON.parse(client.browseMovieAndTelevision(2,7))
                                else if(category.text === "科幻")
                                    drame.drames = JSON.parse(client.browseMovieAndTelevision(2,8))
                                load_drame_page(category.text)
                            }
                        }
                    }
                }
            }

            Row{
                id:row_image_drame
                Rectangle{
                    id:slide_drame_image
                    height: mainWindow.width < 1200 ? 342 : 442
                    width: drame.width
//                    width: mainWindow.width < 1200 ? 702 : 950
//                    height: mainWindow.width < 1200 ? 342 : 442
                    color: "red"
                    Image {
                        id: drame_image
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
                id: slide_drame
                width:  mainWindow.width < 1200 ? 1000 : 1200
                height: 40
                opacity: 0.8
                anchors.top: row_image_drame.top
                anchors.left: row_image_drame.left
                anchors.right: row_image_drame.right
                anchors.topMargin: mainWindow.width < 1200 ? 302 : 404
                orientation: ListView.Horizontal
                z:5
                model:recommendDrames.firstRecommends
                delegate: show_drame_slide
            }

            Component{
                id:show_drame_slide
                Rectangle{
                    id: slideRect_drame
                    width: row_image_drame.width/5
                    height: 40//slide_drame_image.height / 5
                    color:ListView.isCurrentItem ? "lightblue" : "white"
                    onColorChanged: {
                        drame_image.source = "file:" + modelData.post
                    }
                    Text {
                        id: slideDrame_name
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
                            if(slideRect_drame.ListView.view.currentIndex !== index){
                                slideRect_drame.ListView.view.currentIndex = index;
                            }
                            time_drame.stop()
                        }
                        onExited: {
                            time_drame.restart()

                        }
                    }
                }
            }

            ColumnLayout{
                anchors.top: row_image_drame.bottom
                anchors.topMargin: 20
                spacing: page_display.width < 1000 ? 10 : 60

                Repeater{
                    id:show_drame
                    model:recommendDrames.secondRecommends.resource
                    Rectangle{
                        width: page_display.width
                        height: page_display.width < 1000 ? 355 : 400
                        Text {
                            id:drame_title
                            text: modelData.title
                            font.pixelSize: 24
                        }

                        Row {
                            id: drame_grid
                            anchors.top: drame_title.bottom
                            anchors.topMargin: 15
                            anchors.left: parent.left
                            spacing: mainWindow.width < 1200 ? 15 : 50
                            Repeater {
                                model: modelData.drames
                                Rectangle {
//                                    width:  mainWindow.width < 1200 ? 175 :225
//                                c    height:  page_display.width < 1000 ? 290 : 370
                                    width:  mainWindow.width < 1200 ? 175 : 197
                                    height:  page_display.width < 1000 ? 290 : 326
                                    Rectangle {
                                        id: collectiob_img_drame
                                        width: parent.width
//                                        height:  page_display.width < 1000 ? 263 : 340
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

                                                middleArea.middle = false
                                                if(playInterface.playCommponent.playing)
                                                {
                                                    playInterface.playCommponent.stopPlay()
                                                    console.log("true")
                                                }

//                                                play.rtspUrl = modelData.rtspURL
                                                play.esipode = Number(epText.text)
                                                play.rtspUrl = middleArea.playRtspUrl + "/0.mkv"

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
                                        id: collectiob_text_drame
                                        width: parent.width
                                        text: modelData.name
                                        wrapMode: Text.Wrap
                                        anchors.top: collectiob_img_drame.bottom
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
        id:time_drame
        interval: 3000
        running: true
        repeat: true
        onTriggered:{
            if(slide_drame.currentIndex ===  4)
            {
                slide_drame.currentIndex -= 4

            }else{
                slide_drame.currentIndex += 1
            }
        }
    }


    function load_drame_page(page){
        switch(page){
        case "推荐":
            drame_stack.push(recommend_drame,StackView.Immediate)
            break
        default:
            drame_stack.push(common_drame,StackView.Immediate)
            break
        }
    }
}
