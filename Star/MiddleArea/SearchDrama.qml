import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2

Rectangle {
    id: drama
    height: parent.height
    width: parent.width
    anchors.fill: parent
    property var searchDrama: middleArea.middleface.searchDrama

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
                        search_stack.pop()
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
                        search_stack.clear()
                        middle_Menu.visible = true
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
                    model: searchDrama
                    Rectangle{
                        width: showlist.width
                        height: 0
                        border.width: 1
                        border.color: "lightgray"
                        Rectangle{
                            id:showposter
                            width: 150
                            height: 240
                            anchors.left: parent.left
                            anchors.leftMargin: 25
                            anchors.top: parent.top
                            anchors.topMargin: 20
                            border.width: 2
                            border.color: "gray"

                            Image {   //显示海报
                                id: poster
                                width:150
                                height: 240
                                anchors.fill: parent
                                source: "file:" + modelData.post
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
                            id: intro
                            width: parent.width - 240
                            height: 90
                            anchors.left: showposter.right
                            anchors.leftMargin: 20
                            anchors.top: movietitle.bottom
                            anchors.topMargin: 20
                            font.pixelSize: 12
                            wrapMode: Text.WrapAnywhere
                            lineHeight: 1
                            text: modelData.introduction
                        }
                        GridLayout{
                            id:griddrame
                            width: 560
                            height: 100
                            columns: 9
                            columnSpacing: 2
                            rowSpacing: 5
                            anchors.left: showposter.right
                            anchors.leftMargin: 20
                            anchors.top: intro.bottom
                            anchors.topMargin: 10
                            Repeater{
                                model:modelData.episode

                                Rectangle{   //播放按钮
                                    id: playbutton
                                    width: 20
                                    height: 20
                                    color: "#8b8378"
                                    MouseArea{
                                        id:playmousearea
                                        anchors.fill: parent
                                        hoverEnabled: true
                                        onClicked: {
                                            playbutton.color = "red"
                                        }
                                    }

                                    Text {
                                        id: drametitle
                                        anchors.horizontalCenter: playbutton.horizontalCenter
                                        anchors.verticalCenter: playbutton.verticalCenter
                                        font.pixelSize: 12
                                        color: "lightblue"
                                        text: modelData + 1
                                    }
                                }
                            }
                        }
                    }
                }
            }

        }  //showlist
    }//showrectangle
}//searchpage
