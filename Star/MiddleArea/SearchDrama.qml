import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2

Rectangle {
    id: drama
    height: parent.height
    width: parent.width
    anchors.fill: parent
    property var searchDrama: middleArea.middleface.searchDrama

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
    }

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
                        height: 300
                        border.width: 1
                        border.color: "lightgray"
                        Rectangle{
                            id:showposter
                            width: 150
                            height: 240
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
//                        Text{     //显示简介
//                            id: intro
//                            width: parent.width - 240
//                            height: 50
//                            anchors.left: showposter.right
//                            anchors.leftMargin: 20
//                            anchors.top: movietitle.bottom
//                            anchors.topMargin: 20
//                            font.pixelSize: 12
//                            wrapMode: Text.WrapAnywhere
//                            lineHeight: 1
//                            //                            text:movie[0].introduction
//                            text: qsTr("简介：表面上无限风光的苏家，随着苏母的突然离世，瞬间分崩离析。意想不到的隐患层层显露，对毫无主见却又自私、小气的苏父的安置和后续生活问题，打破了远在国外的大哥与本城的二哥 、小妹三家的平静生活。父亲苏大强终于摆脱了妻子的铁腕，对几个孩子变本加厉，不断提出过分要求。在美国工作的老大苏明哲回到国内，一心要挑起家庭重担，...")
//                        }
                        GridLayout{
                            id:griddrame
                            width: 560
                            height: 100
                            columns: 10
                            columnSpacing: 5
                            rowSpacing: 5
                            anchors.left: showposter.right
                            anchors.leftMargin: 20
                            anchors.bottom: parent.bottom
                            anchors.bottomMargin: 20
                            Repeater{
                                model:12

                                Rectangle{   //播放按钮
                                    id: playbutton
                                    width: 20
                                    height: 20
                                    color: "blue"
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
                                        font.pixelSize: 18
                                        color: "lightblue"
                                        text: qsTr("1")
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
