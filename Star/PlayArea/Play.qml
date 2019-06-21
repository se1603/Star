/*
 * Date :2019.4.27
 * Author:xudan
 *
 * Date :2019.4.27
 * Author:xudan
 * 内容：播放主界面
 *
 * Author:王梦娟
 * Date:2019-5-25
 * Note:修改MouseArea覆盖的问题
*/

import QtQuick 2.9
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "../MiddleArea"

Rectangle {
    id:play
    visible: true
    width: middleArea.width
    height: middleArea.height

    property alias playwidth: play.width
    property bool xflag: play.name ? true :false

    property bool xRflag: true
    property string name:""
    property string type: ""
    property string infoma:""
    property string image:""

    property var datas
    property var commentModel

    property int esipode: 1

    property string rtspUrl: ""
//    property bool playing: false
    property alias playCommponent: playVideo

    Rectangle{
        id:center
        anchors.right: rightRec.left
        anchors.left: leftRect.right
        height: parent.height
//        color:"green"

        PlayVideo{
            id:playVideo
            visible: play.name ? true :false
            path: rtspUrl
        }
        Rectangle{
            visible: play.name ? false :true
            width: parent.width
            height: parent.height
            color:  "#8B8378"
            Text{
                anchors.centerIn: parent
                text: "请选择视频播放"
                font.pixelSize: 28
                color: "white"
            }
        }
    }

    //组合动画
    ParallelAnimation{
        id: menuStartAnim //属性动画
        NumberAnimation{
            target: rightRec
            properties: "x"
            from: 4/5*play.width//-200
            to: play.width //动画持续时间，毫秒
            duration: 500 //动画渐变曲线
            easing.type: Easing.OutQuad
        }
    }
    ParallelAnimation{
        id: menuStopAnim
        NumberAnimation{
            target: rightRec
            properties: "x"
            from: play.width
            to: 4/5*play.width//-200
            duration: 500
            easing.type: Easing.Linear }
    }

    onVisibleChanged: {
            right_stack.push(comment_page,StackView.Immediate)
    }
    Rectangle{
        id:rightRec
        x: xflag ? 4/5*play.width : play.width//200
        y:0
        width: 1/5*play.width//200
        height: play.height
        radius: 5

        Rectangle {
            id:rightmenu
            anchors.top: parent.top
            width: parent.width
            height: 1/13*play.height //- 10
            color: "#424242"
            Rectangle{
                id:leftM
                anchors.left: parent.left
                anchors.top:parent.top
                anchors.topMargin: 10
                width: 1/2*parent.width-8
                height: parent.height-20
                color: "#424242"
                Button{
                    anchors.fill: parent
                    text: "简介"
                    onClicked: {
                        right_stack.push(comment_page,StackView.Immediate)
                    }
                }
            }

            Rectangle{
                anchors.top:parent.top
                anchors.topMargin: 10
                anchors.left:leftM.right
                anchors.leftMargin: 15
                width: 1/2*parent.width-8
                height: parent.height-20
                color: "#424242"
                Button{
                    anchors.fill: parent
                    text: "评论"
                    onClicked: {
                        right_stack.push(summary_page,StackView.Immediate)
                    }
                }
            }
        }


        StackView{
            width: parent.width
            height: 12/13*play.height
            anchors{
                left: parent.left
                right: parent.right
                bottom: parent.bottom
                top: toolBar.bottom
            }
            id:right_stack
            initialItem: comment_page
            MouseArea{
                anchors.fill: parent
            }
        }

        Component{
            id:summary_page
            Comment{
                //                vect:commentModel
            }
        }
        Component{
            id:comment_page
            Program{
                id:e
            }
        }
    }

    Rectangle{
        id:leftRect
        x:xRflag ? 0 : -1/5*play.width
        y:0
        width: 1/5*play.width
        height: play.height
        color: "#424242"
        Rectangle{
            id:toolBar
            anchors.top: parent.top
            width: parent.width
            height: 1/13*play.height
            color: "#424242"
            Rectangle{
                id:libraryRec
                anchors.left: parent.left
                anchors.leftMargin: 5
                anchors.top:parent.top
                anchors.topMargin: 5
                width: 1/4*parent.width
                height: parent.height-20
                color: "#424242"
                Button{
                    anchors.fill: parent
                    text: qsTr("片库")
                    onClicked: left_stack.push(library_page)
                }
            }
            Rectangle{
                id:localrect
                anchors.top:parent.top
                anchors.topMargin: 5
                anchors.left: libraryRec.right
                anchors.leftMargin: 15
                anchors.right: recordRect.left
                anchors.rightMargin: 15
                width: 1/4*parent.width
                height: parent.height-20
                color: "#424242"
                Button{
                    anchors.fill:parent
                    text: qsTr("本地")
                    onClicked: left_stack.push(local_page)
                }
            }
            Rectangle{
                id:recordRect
                anchors.top:parent.top
                anchors.topMargin: 5
                anchors.right: parent.right
                anchors.rightMargin: 10
                width: 1/4*parent.width
                height: parent.height-20
                color: "#424242"
                Button{
                    anchors.fill:parent
                    text: qsTr("记录")
                    onClicked: left_stack.push(record_page)
                }
            }
        }


        StackView{
            width: parent.width
            height: 12/13*play.height
            anchors{
                left: parent.left
                right: parent.right
                bottom: parent.bottom
                top: toolBar.bottom
            }

            MouseArea{
                anchors.fill: parent
            }
            id:left_stack
            initialItem: library_page
        }
        Component{
            id:local_page
            Local{

            }
        }
        Component{
            id:record_page
            Record{}
        }

        Component{
            id:library_page
            FilmLibraty{
            }
        }
    }

    //组合动画
    ParallelAnimation{
        id: leftStartAnim //属性动画
        NumberAnimation{
            target: leftRect
            properties: "x"
            from:0
            to: -1/5*play.width//动画持续时间，毫秒
            duration: 500 //动画渐变曲线
            easing.type: Easing.OutQuad }
    }

    ParallelAnimation{
        id: leftStopAnim
        NumberAnimation{
            target: leftRect
            properties: "x"
            from:-1/5*play.width
            to: 0
            duration: 500
            easing.type: Easing.Linear
        }
    }

}
