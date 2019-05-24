import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Rectangle {
    width: page_display.width
    height: page_display.height

    property var recommendVarieties:JSON.parse(client.showRecommend(4))

    ScrollView {
        anchors.fill: parent
        clip: true
        ColumnLayout {
            width: parent.width
            height: parent.height

            Row {
                anchors.left: parent.left
                spacing: 50
                Repeater {
                    model: JSON.parse(client.showCategory(4))
                    delegate: variety_category
                }
            }

            Row {
                id: row_image
                Rectangle {
                    id: row_rec
                    width: mainWindow.width < 1200 ? 702 : 950
                    height: mainWindow.width < 1200 ? 342 : 442

                    Image {
                        id: slide_image
                        width: parent.width
                        height: parent.height
                    }
                    MouseArea {
                        anchors.fill: parent
                    }
                }
            }

            ListView {
                id: slide_varieties
                width: parent.width
                height: row_rec.height
                anchors.top: row_image.top
                anchors.left: row_image.right
                model: recommendVarieties.firstRecommends
                delegate: variety_slide
            }

            ColumnLayout{
                anchors.top: slide_varieties.bottom
                anchors.topMargin: 20
                spacing: page_display.width < 1000 ? 10 : 60

                Repeater{
                    id: show_variety
                    model: recommendVarieties.secondRecommends.resource
                    Rectangle{
                        width: page_display.width
                        height: page_display.width < 1000 ? 355 : 400
                        Text {
                            id: recommend_title
                            text: modelData.title
                            font.pixelSize: 24
                        }

                        Row {
                            id: variety_grid
                            anchors.top: recommend_title.bottom
                            anchors.topMargin: 15
                            anchors.left: parent.left
                            spacing: mainWindow.width < 1200 ? 15 : 50
                            Repeater {
                                model: modelData.varieties
                                Rectangle {
                                    width: mainWindow.width < 1200 ? 175 : 197
                                    height: page_display.width < 1000 ? 290 : 326
                                    Rectangle {
                                        id: collection_img
                                        width: parent.width
                                        height:  page_display.width < 1000 ? 263 : 296
                                        Image {
                                            anchors.fill: parent
                                            anchors.top: parent.top
                                            source: "file:" + modelData.post
                                        }

                                        MouseArea{
                                            anchors.fill: parent
                                            onClicked: {
                                                console.log(modelData.name)
                                                console.log(modelData.post)
                                                play.visible = true
                                                play.name = modelData.name
                                                play.image = modelData.post
                                                play.datas = JSON.parse(client.getMovieInfo(modelData.name,4))
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
        id: time
        interval: 3000
        running: true
        repeat: true
        onTriggered: {
            if(slide_varieties.currentIndex === 4)
                slide_varieties.currentIndex -= 4
            else
                slide_varieties.currentIndex += 1
        }
    }

    Component {
        id: variety_category
        Rectangle {
            width: 50
            height: 40
            Text {
                id: category
                text: modelData.category
                opacity: 0.5
                font.pixelSize: 15
                color: 	"#808080"
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
                            variety.varieties = JSON.parse(client.browseMovieAndTelevision(4,1))
                        else if(category.text === "选秀")
                            variety.varieties = JSON.parse(client.browseMovieAndTelevision(4,2))
                        else if(category.text === "美食")
                            variety.varieties = JSON.parse(client.browseMovieAndTelevision(4,3))
                        else if(category.text === "旅游")
                            variety.varieties = JSON.parse(client.browseMovieAndTelevision(4,4))
                        else if(category.text === "纪实")
                            variety.varieties = JSON.parse(client.browseMovieAndTelevision(4,5))
                        else if(category.text === "搞笑")
                            variety.varieties = JSON.parse(client.browseMovieAndTelevision(4,6))
                        else if(category.text === "访谈")
                            variety.varieties = JSON.parse(client.browseMovieAndTelevision(4,7))
                        load_page(category.text)
                    }
                }
            }
        }
    }

    Component {
        id: variety_slide
        Rectangle {
            id: slide_rec
            width: 250
            height: 1 / 5 * row_rec.height
            color: ListView.isCurrentItem ? "lightblue" : "white"
            onColorChanged: {
                slide_image.source = "file:" + modelData.post
            }
            Text {
                id: slide_name
                text: modelData.name
                anchors.centerIn: parent
                color: "black"
            }
            MouseArea {
                anchors.fill: parent
                acceptedButtons: Qt.RightButton | Qt.LeftButton
                hoverEnabled: true
                propagateComposedEvents: true
                enabled: true

                onClicked: {
                }
                onEntered: {
                    if(slide_rec.ListView.view.currentIndex !== index){
                        slide_rec.ListView.view.currentIndex = index;
                    }
                    time.stop();
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
            variety_stack.push(recommend_variety,StackView.Immediate)
            break
        default:
            variety_stack.push(common_variety,StackView.Immediate)
        }
    }
}
