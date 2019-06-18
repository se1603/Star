import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtGraphicalEffects 1.0

Rectangle {
    id: dircector
    height: parent.height
    width: parent.width
    anchors.fill: parent
    property var searchDirector: middleArea.middleface.searchDirector

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
                    }
                }
            }
        }
    } //toprectangle

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
        Rectangle{ //显示搜索内容
            id:showdetails
            width: 4/5 * parent.width
            height: parent.height-40
            anchors.top: relation.bottom
            anchors.left: parent.left
            Column{
                anchors.top: parent.top
                anchors.left: parent.left
                spacing: 10
                Repeater{
                    model: searchDirector
                    Rectangle{
                        id:actordetail
                        width: parent.width
                        height: 200
                        anchors.top: parent.top
                        anchors.left: parent.left
                        Rectangle{
                            id:actorpost
                            width: 150
                            height: 150
                            radius: 75
                            anchors.left: parent.left
                            anchors.leftMargin: 30
                            anchors.verticalCenter: parent.verticalCenter
                            Image {
                                id: dirctorpost
                                anchors.fill: parent
                                sourceSize: Qt.size(parent.width, parent.height)
                                smooth: true
                                visible: false
                                source: "file:" + modelData.post
                            }
                            Rectangle{
                                id: mask
                                anchors.fill: parent
                                radius: width / 2
                                visible: false
                                antialiasing: true
                                smooth: true
                            }

                            OpacityMask{
                                anchors.fill: dirctorpost
                                source: dirctorpost
                                maskSource: mask
                                visible: true
                                antialiasing: true
                            }
                        }
                        Text{   //显示姓名
                            id: actorname
                            width: 100
                            height: 35
                            anchors.left: actorpost.right
                            anchors.leftMargin: 20
                            anchors.top: parent.top
                            anchors.topMargin: 20
                            font.pixelSize: 24
                            color: "lightblue"
                            text: modelData.name
                        }
                    }
                }
            }
        }
    }
}  //actor

