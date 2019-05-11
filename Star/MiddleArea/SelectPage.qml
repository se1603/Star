import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Rectangle {
    id:selectPage
    width: page_display.width
    height: page_display.height


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
                    Text{
                        id:te

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
                model:listModel1//recommendFilms.firstRecommends
                delegate: show_slide
            }

            ColumnLayout{
                anchors.top:slideImage.bottom
                anchors.topMargin: 20
                spacing: page_display.width < 1000 ? 10 : 60

                Repeater{
                    id:show_film
                    model:5//recommendFilms.secondRecommends.resource
                    Rectangle{
                        width: page_display.width
                        height: page_display.width < 1000 ? 355 : 400
                        Text {
                            id:recommend_title
                            text: modelData
                            font.pixelSize: 24
                        }

                        Row {
                            id: film_grid
                            anchors.top: recommend_title.bottom
                            anchors.topMargin: 15
                            anchors.left: parent.left
                            spacing: mainWindow.width < 1200 ? 15 : 50
                            Repeater {
                                model: 5//modelData.films
                                Rectangle {
                                    width:  mainWindow.width < 1200 ? 175 : 197
                                    height:  page_display.width < 1000 ? 290 : 326
                                    Rectangle {
                                        id: collection_img
                                        width: parent.width
                                        height:  page_display.width < 1000 ? 263 : 296
                                        color: "red"

                                        MouseArea{
                                            anchors.fill: parent
                                            onClicked: {

                                            }
                                        }
                                    }
                                    Text {
                                        id: collection_text
                                        width: parent.width
                                        text: modelData
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
                te.text = icon
            }
            Text {
                id: slideFilm_name
                text: tex//modelData
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

    ListModel{
        id:listModel1
        ListElement{
            tex:"ddd"
            icon:"vvvdsd"
        }

        ListElement{
            tex:"ddd1"
            icon:"vvv1dsd"
        }
        ListElement{
            tex:"ddd2"
            icon:"vvvd2sd"
        }
        ListElement{
            tex:"ddd3"
            icon:"vvvds3d"
        }
        ListElement{
            tex:"ddd4"
            icon:"vvvdsd4"
        }
    }
}
