/*author:古长蓉
 *data:2019-05-12
 * 显示分类页面
 */
import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Rectangle {
    width: page_display.width
    height: page_display.height

    property var mydrame:drame.drames

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
                    model:JSON.parse(client.showCategory(2))
                    delegate: drameDelegate
                }
            }
            Component{
                id:drameDelegate
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
                                load_page(category.text)
                            }
                        }
                    }
                }
            }

            GridLayout {
                id: drame_grid
                anchors.top: row_menu.bottom
                anchors.topMargin: 15
                anchors.left: parent.left
                anchors.leftMargin: 15
                columns: page_display.width < 1000 ? 4 : 5
                columnSpacing: page_display.width < 1000 ? 15 : 20
                rowSpacing: 15
                Repeater {
                    model: mydrame
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
                            id: dramename
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
                            anchors.top: dramename.top
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
                                console.log(modelData.name)
                                console.log(modelData.post)

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

    function load_page(page){
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

