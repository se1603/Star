import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Rectangle {
    id:selectPage

    width: /*59 / 60 **/page_display.width
    height: 59 / 60 *page_display.height

    ScrollView {
        anchors.fill: parent
        clip: true
        ColumnLayout {
            width: parent.width
            height: parent.height

            Row{
                id:slide
                width: parent.width
                height: 300
                Rectangle{
                    id:image_re
                    width: 4/5*selectPage.width
                    height: 300
                    color: "red"
                    Text{
                        id:dd
                    }
                }
                ListView{
                    id:slideView
                    width: 1/5*selectPage.width
                    height: 300//selectPage.height
                    anchors.top:image_re.top
                    anchors.topMargin: 5
                    anchors.left: image_re.right
                    model: listModel1
                    delegate: slide_de
                }
            }



            Column{
                anchors.top:slide.bottom
                anchors.topMargin: 20
                spacing: 10
                Repeater{
                    model: selectModel2
                    Rectangle {
                        id:item
                        width:selectPage.width
                        height:370
                        Text { id: nameField; text: name }

                        GridLayout{
                            id:grid
                            columns:4
                            width: parent.width
                            anchors.top:nameField.bottom
                            //                columnSpacing: 10
                            rowSpacing: 20
                            Repeater {
                                model: attributes
                                Rectangle{
                                    width: 1/5 * item.width + 10
                                    height: 150
                                    color: "#dd22dd"
                                    Text{
                                        anchors.top: parent.bottom
                                        text: url
                                    }
                                    MouseArea{
                                        anchors.fill: parent
                                        onClicked: {
                                            play.visible = true
                                            play.name = url
                                            play.type = type
                                            play.model = model
                                            play.infoma = type
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }


    ListModel {
        id: selectModel2

        ListElement{
            name:"动漫精选"
            attributes:[
                ListElement{
                    url:"动漫精选1"
                    type:"sss sss"
                    model:"15"
                },
                ListElement{
                    url:"动漫精选2"
                    type:"ss1s sss"
                    model:"15"
                },
                ListElement{
                    url:"动漫精选3"
                    type:"sss s1ss"
                    model:"15"
                },
                ListElement{
                    url:"动漫精选4"
                    type:"sfsss sss"
                    model:"15"
                },
                ListElement{
                    url:"动漫精选5"
                    type:"sssd sss"
                    model:"15"
                }
            ]
        }

        ListElement{
            name:"电影精选"
            attributes:[
                ListElement{
                    url:"电影精选1"
                    type:"sss sssgs"
                    model:"0"
                },
                ListElement{
                    url:"电影精选2"
                    type:"ssss4 sss"
                    model:"0"
                },
                ListElement{
                    url:"电影精选3"
                    type:"sss esss"
                    model:"0"
                },
                ListElement{
                    url:"电影精选4"
                    model:"0"
                },
                ListElement{
                    url:"电影精选5"
                    type:"sss5s sss"
                    model:"0"
                }
            ]
        }
        ListElement{
            name:"剧集精选"
            attributes:[
                ListElement{
                    url:"剧集精选1"
                    type:"sss 2sss"
                },
                ListElement{
                    url:"剧集精选2"
                    type:"sss ssqs"
                },
                ListElement{
                    url:"剧集精选3"
                    type:"ssws sss"
                },
                ListElement{
                    url:"剧集精选4"
                    type:"ssws sss"
                },
                ListElement{
                    url:"剧集精选5"
                    type:"swss 3sss"
                }
            ]
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

    Timer {
        id:time
        interval: 3000
        running: true
        repeat: true
        onTriggered:{
            if(slideView.currentIndex ==  4)
            {
                slideView.currentIndex -= 4

            }else{
                slideView.currentIndex += 1
            }
        }
    }

    Component{
        id:slide_de
        Rectangle{
            id:slideRect
            width: 1/5*selectPage.width
            height: 1/5*image_re.height
            border.color: "lightblue"
            color:ListView.isCurrentItem ? "lightblue" : "white"
            onColorChanged: {
                dd.text=icon
            }
            Text {
                id: te
                text: tex
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
                    if(slideRect.ListView.view.currentIndex != index){
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
