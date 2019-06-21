/*author:guchanrong
 *data:2019-05-21
 *显示搜索的电影
 */
import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import "../TopArea"

Rectangle {
    id: movie
    height: parent.height
    width: parent.width
    anchors.fill: parent
    property var searchMovie: middleArea.middleface.searchMovie

    //顶部提示栏
    Rectangle{
        id:toprectangle
        width: parent.width
        height: 1/20 * parent.height
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        //后退按钮，回到主页面
        Rectangle{
            id: backbutton
            width: 50
            height: parent.height
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.verticalCenter: toprectangle.verticalCenter
            color: "#00CDCD"
            Image {
                id: backicon
                height: 30
                width: 50
                anchors.right: backbutton.right
                anchors.rightMargin: 0
                anchors.verticalCenter: parent.verticalCenter
                opacity: bakcmousearea.containsMouse ? 1.0 : 0.5
                source: "qrc:/image/TopArea/back.jpg"
                MouseArea{
                    id:bakcmousearea
                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked: {
                        if(search_stack.depth > 2) {
                            search_stack.pop()
                        } else {
                            middle_stack.pop(select_page)
                            middleArea.middleface.search.visible = false
                        }
                    }
                }
            }
        }
        //关闭按钮，回到主页面
        Rectangle{
            id: closebutton
            width: 50
            height: parent.height
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.verticalCenter: toprectangle.verticalCenter
            color: "red"
            Image {
                id: closeicon
                height: 20
                width: 35
                anchors.right: closebutton.right
                anchors.rightMargin: 5
                anchors.verticalCenter: parent.verticalCenter
                opacity: closemousearea.containsMouse ? 1.0 : 0.5
                source: "qrc:/image/TopArea/close.png"
                MouseArea{
                    id:closemousearea
                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked: {
                        middle_stack.pop(select_page)
                        middleArea.middleface.search.visible = false
                    }
                }
            }
        }
    }

    //显示信息栏
    Rectangle{
        id:showrectanggle
        width: parent.width-50
        height: 19/20 * parent.height
        anchors.top: toprectangle.bottom
        anchors.left: parent.left
        anchors.leftMargin: 50
        anchors.verticalCenter: parent.verticalCenter
        //        color: "gray"

        Rectangle{  //提示搜索内容
            id:relation
            height: 40
            width: parent.width
            anchors.top: toprectangle.bottom
            anchors.left: parent.left
            //            color: "#FAF0E6"
            Row{
                id:rowbutton
                spacing: 10
                anchors.left: parent.left
                Rectangle{
                    id:button1
                    width: 40
                    height: 30
                    border.width: 1
                    border.color: "gray"
                    Text {
                        id: button1text
                        anchors.centerIn: parent
                        text: qsTr("相关")
                    }
                }
                Rectangle{
                    id:button2
                    width: 40
                    height: 30
                    border.width: 1
                    border.color: "gray"
                    Text {
                        id: button2text
                        anchors.centerIn: parent
                        text: qsTr("最新")
                    }
                }
                Rectangle{
                    id:button3
                    width: 40
                    height: 30
                    border.width: 1
                    border.color: "gray"
                    Text {
                        id: button3text
                        anchors.centerIn: parent
                        text: qsTr("最热")
                    }
                }
            }
        }
        Rectangle{   //将搜索的内容以列表的形式显示
            id:showlist
            width: 4/5 * parent.width
            height: parent.height-40
            anchors.top: relation.bottom
            anchors.left: parent.left

            Column{
                anchors.top: parent.top
                anchors.left: parent.left
                spacing: 10
                Repeater{
                    model: searchMovie
                    Rectangle{
                        width: showlist.width
                        height: 200
                        border.width: 1
                        border.color: "lightgray"
                        Rectangle{
                            id:showposter
                            width: 120
                            height: 180
                            anchors.left: parent.left
                            anchors.leftMargin: 25
                            anchors.verticalCenter: parent.verticalCenter
                            border.width: 2
                            border.color: "gray"

                            Image {   //显示海报
                                id: poster
                                width:120
                                height: 180
                                anchors.fill: parent
                                source: "file:" + modelData.post
                                MouseArea{
                                    anchors.fill: parent
                                    onClicked: {
                                        console.log(poster.source)
                                    }
                                }
                            }


                        }
                        Text{   //显示影视节目名称
                            id: movietitle
                            width: 100
                            height: 35
                            anchors.left: showposter.right
                            anchors.leftMargin: 20
                            anchors.top: parent.top
                            anchors.topMargin: 20
                            font.pixelSize: 24
                            color: "lightblue"
                            text: modelData.name
                        }
                        Text{     //显示简介
                            id: movieintro
                            width: parent.width - 240
                            height: 50
                            anchors.left: showposter.right
                            anchors.leftMargin: 20
                            anchors.top: movietitle.bottom
                            anchors.topMargin: 20
                            font.pixelSize: 12
                            wrapMode: Text.WrapAnywhere
                            lineHeight: 1
                            text:modelData.introduction
                        }
                        Rectangle{   //播放按钮
                            id: playbutton
                            width: 80
                            height: 30
                            color: "#FFEFD5"
                            anchors.left: showposter.right
                            anchors.leftMargin: 50
//                            anchors.top: movieintro.bottom
//                            anchors.topMargin: 30
                            anchors.bottom: parent.bottom
                            anchors.bottomMargin: 30
                            MouseArea{
                                id:playmousearea
                                anchors.fill: parent
                                hoverEnabled: true
                                onClicked: {

                                }
                            }

                            Text {
                                id: buttontitle
                                anchors.horizontalCenter: playbutton.horizontalCenter
                                anchors.verticalCenter: playbutton.verticalCenter
                                font.pixelSize: 18
                                color: "lightblue"
                                text: qsTr("开始播放")
                            }
                        }
                    }
                }
            }

        }  //showlist
    }//showrectangle
    function load_page(page){
            search_stack.push(searchmovie, StackView.Immediate)
    }
}//searchpage
