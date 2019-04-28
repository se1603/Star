//徐丹   12月15号
//此界面实现滑动效果

import QtQuick 2.0
import QtQuick.Controls 2.2
//import StarPlayer 1.0

Item {
    id: slide
    visible: true
    width: parent.width
    height: 4/15 * parent.height

    //定时器，控制图片自动滑动
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



    //显示图片的矩形框，图片来自listModel
    Rectangle{
        id:rect
        width: parent.width-250
        height: slide.height
        color: "red"
        Text{
            id:dd
        }

    }

    ListModel{
        id:listModel
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

    ListView{
        id:slideView
        width: parent.width
        height: parent.height
        anchors.left: rect.right
        anchors.topMargin: 10
        model: listModel
        delegate: con
    }

    Component{
        id:con
        Rectangle{
            id: slideRect
            width: slide.width-rect.width
            height: rect.height/5
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
                    play.visible = true
                    play.thename = rect.moviename
                    play.thesource = rect.movieurl
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
