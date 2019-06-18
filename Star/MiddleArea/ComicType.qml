//time：2019.5.6
//内容：动漫界面填充对应类型的post
//Autor：徐丹
import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Rectangle {
    width: page_display.width
    height: page_display.height
//    color: "yellow"
    property var comics_type: comic.comics

    ScrollView {
            anchors.fill: parent
            clip: true
            ColumnLayout {
                width: parent.width
                height: parent.height

                Row{
                    id: row_menu1
                    anchors.left:parent.left
                    spacing: 50
                    Repeater {
                        model:JSON.parse(client.showCategory(3))
                        delegate: comicDelegate
                    }
                }

                GridLayout {
                    id: comicGrid
                    anchors.top: row_menu1.bottom
                    anchors.topMargin: 15
                    anchors.left: parent.left
                    anchors.leftMargin: 15
                    columns: page_display.width < 1000 ? 4 : 5
                    columnSpacing: page_display.width < 1000 ? 15 : 20
                    rowSpacing: 15
                    Repeater {
                        model: comics_type
                        Rectangle {
                            id:comicImage
                            width: page_display.width < 1000 ? 220 :230 //220
                            height: page_display.width < 1000 ? 330 : 340
//                            border.color: "red"
                            Image {
                                anchors.fill: parent
                                anchors.top: parent.top
                                source:"file:" + modelData.post
                            }
                            Rectangle {
                                id: comicName
                                width: parent.width
                                height: 30
                                anchors.bottom: parent.bottom
//                                border.color : "green"
                            }
                            Text {
                                id: collection_text1
                                width: parent.width
                                text: modelData.name
                                font.pixelSize: 15
                                wrapMode: Text.Wrap
                                anchors.top: comicName.top
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

                                    play.rtspUrl = modelData.rtspURL

                                    play.visible = true
                                    play.name = modelData.name
                                    play.image = modelData.post
                                    console.log(modelData.name)
                                    console.log(modelData.post)
                                    play.datas = JSON.parse(client.getMovieInfo(modelData.name))
//                                    play.commentModel = JSON.parse(client.showCommentInfo(play.name))
                                    console.log(play.datas.resource.videotype.type)

                                    if(modelData.name !== middleArea.playingName
                                            && middleArea.playingName!==""){
                                        client.addRecord(audienceInterface.audienceName,middleArea.playingName,middleArea.startTime,middleArea.duration,middleArea.videoType)
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
        id:comicDelegate
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
                        load_page(category.text)
//                        load_page(comic_category.text)
                    }
                }
            }
        }
    }

    function load_page(page){
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
