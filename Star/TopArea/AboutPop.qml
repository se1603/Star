import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.2

Dialog {
    id:aboutpop
    width: 400//parent.width
    height: 300//parent.height

//    background:  Rectangle{
//        width: parent.width
//        height: parent.height
//    }

//    x:-600
//    y:200

//        Text{
//            width:parent.width
//            wrapMode: Text.Wrap
//            anchors.top: parent.top
//            color: "black"
//            z:3
//            font.pixelSize: 24
//            text: "关于"
//        }
//        Rectangle{
//            z:3
//            anchors.top: parent.top
//            anchors.right: parent.right
//            width: colse.implicitWidth
//            height: colse.implicitHeight
//            Text{
//                id:colse
//                color: "black"
//                text: "关闭"
//                font.pixelSize: 18
//            }
//            MouseArea{
//                anchors.fill: parent
//                onClicked: {
//                    about.close()
//                }
//            }
//        }

    Rectangle{
        width: 350
        height: 250
        anchors.centerIn: parent
        Rectangle{
            id:rec
            width: 100
            height: 50
            anchors.top: parent.top
            anchors.topMargin: 65
            anchors.left: parent.left
            anchors.leftMargin: 25
            Image {
                id: stIcon
                source: "qrc:/image/TopArea/StarIcon.png"
                width: parent.width
                height: parent.height
                anchors.verticalCenter: parent.verticalCenter
            }
        }
            Text{
                width:150//parent.width
                wrapMode: Text.Wrap
                anchors.top: parent.top
                anchors.topMargin: 65
                anchors.left: rec.right
                anchors.leftMargin: 10
                color: "black"
                font.pixelSize: 20
                text: "StarPlayer V1.0 基于QT开发环境"
            }
    }

}
