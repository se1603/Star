//time :2019.4.27
//author:xudan

import QtQuick 2.9
//import QtQuick.Window 2.2
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import"../MiddleArea"
Item {
    id:play
    visible: true
    width: parent.width
    height: parent.height

    property bool xflag: true
    property bool xRflag: true

    Timer{
        id:timer1
        interval: 2000
        running: false
        onTriggered: {
            leftbu.width = 0
            rightbt.width=0
        }
    }

    Rectangle{
        id:center
        anchors.right: rightRec.left
        anchors.left: leftRect.right
        height: parent.height
        color:"lightblue"

        MouseArea{
            anchors.fill: parent
            hoverEnabled: true
            onEntered: {
                leftbu.width = 20
                rightbt.width = 20
            }
            onExited: {
                timer1.start()
            }
        }
        Rectangle{
            id:rightbt
            y:play.height/2
            anchors.right: center.right
            width: 20
            height: 30
            opacity: 0.5
            Image{
                id:rightButton
                opacity: 1
                mirror: true
                anchors.fill: parent
                source: "qrc:/image/img/left.png"
            }
            MouseArea{
                id:rightMouse
                anchors.fill: parent
                hoverEnabled: true
                onClicked: {
                    if(rightRec.x === play.width){
                        menuStopAnim.start()
                        xflag = ture
                    }else{
                        menuStartAnim.start()
                        xflag = false
                    }
                }
            }
        }

        //左箭头，点击，会回到前一张图片
        Rectangle{
            id:leftbu
            y:play.height/2
            anchors.left: center.left
            width: 20
            height: 30
            opacity: 0.5
            Image{
                id:leftButton
                anchors.fill: parent
                opacity: 1
                source: "qrc:/image/img/left.png"
            }
            MouseArea{
                id:leftMouse
                anchors.fill: parent
                hoverEnabled: true
                propagateComposedEvents: true
                onClicked: {
                    if(leftRect.x === 0){
                        leftStartAnim.start()
                        xRflag = false
                    }else{
                        leftStopAnim.start()
                        xRflag = true
                    }
                }
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


    Rectangle{
        id:rightRec
        x:xflag ? 4/5*play.width : play.width//200
        y:0
        width: 1/5*play.width//200
        height: play.height
//        color:"red"
        radius: 5

        Rectangle {
            id:rightmenu
            anchors.top: parent.top
            width: parent.width
            height: 1/13*leftRect.height - 10
            color: "black"
            Rectangle{
                id:leftM
                anchors.left: parent.left
                anchors.top:parent.top
                anchors.topMargin: 10
                width: 1/2*parent.width-8
                height: parent.height-20
                Button{
                    anchors.centerIn: parent
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
                Button{
                    anchors.centerIn: parent
                    text: "评论"
                    onClicked: {
                        right_stack.push(summary_page,StackView.Immediate)
                    }
                }
            }
        }

        StackView{
            width: parent.width
            height: 12/13*parent.height
            anchors{
                left: parent.left
                right: parent.right
                bottom: parent.bottom
                top: toolBar.bottom
            }
            anchors.topMargin: 20
            id:right_stack
            initialItem: summary_page
        }

        Component{
            id:summary_page
            Summary{

            }
        }
        Component{
            id:comment_page
            Comment{

            }
        }
    }

    Rectangle{
        id:leftRect
        x:xRflag ? 0 : -1/5*play.width
        y:0
        width: 1/5*play.width
        height: play.height
        Rectangle{
            id:toolBar
            anchors.top: parent.top
            width: parent.width
            height: 1/13*leftRect.height - 10
            color: "black"
            Rectangle{
                anchors.left: parent.left
                anchors.leftMargin: 10
                width: 1/3*parent.width
                height: parent.height
                color: "red"
                Button{
                    anchors.fill: parent
                    text: qsTr("Record")
                    onClicked: left_stack.push(record_page)
                }
            }
            Rectangle{
                anchors.right: parent.right
                anchors.rightMargin: 10
                width: 1/3*parent.width
                height: parent.height
                color: "red"
                Button{
                    anchors.fill:parent
                    text: qsTr("Local")
                    onClicked: left_stack.push(local_page)
                }
            }
        }

        StackView{
            width: parent.width
            height: 12/13*parent.height
            anchors{
                left: parent.left
                right: parent.right
                bottom: parent.bottom
                top: toolBar.bottom
            }
            anchors.topMargin: 20
            id:left_stack
            initialItem: record_page
        }
        Component{
            id:local_page
            Local{

            }
        }
        Component{
            id:record_page
            Record{

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
            easing.type: Easing.Linear }
    }
}
