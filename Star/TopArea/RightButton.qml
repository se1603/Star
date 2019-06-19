import QtQuick 2.0
import "../Audience"
import "../MiddleArea"
import QtQuick.Controls 1.4
Item {
    id:rightButton
    width: 1/3 * parent.width
    height: parent.height
    anchors.right: parent.right
    anchors.rightMargin: 5
    anchors.verticalCenter: parent.verticalCenter
    visible: true

    property alias loginPic:login
    property var loginstatus:false
    property var loginname

    Rectangle{     //菜单图标
        id: list
        height: 2/3 * parent.height
        width: 1/15 * parent.width
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        color: "#F5F5F5"
        AboutPop{
            id:about
        }
        Help{
            id:help
        }


        Image {
            id: listicon
            width: 25
            height: 25
            opacity: listmousearea.containsMouse ? 1.0 : 0.5
            anchors.horizontalCenter: list.horizontalCenter
            anchors.verticalCenter: list.verticalCenter
            source: "qrc:/image/TopArea/list.png"
            MouseArea{
                id:listmousearea
                anchors.fill: parent
                hoverEnabled: true
            }
        }
        ComboBox {
            opacity: 0
            currentIndex: 2
            model: ListModel {
                id: cbItems
                ListElement { text: "帮助"; color: "Yellow" }
                ListElement { text: "关于"; color: "Green" }
                ListElement { text: "设置"; color: "Brown" }
            }
            width: 100
            onCurrentIndexChanged: {
                if(cbItems.get(currentIndex).text === "关于"){
                    about.open()
                }
                if(cbItems.get(currentIndex).text === "帮助"){
                    help.open()
                }
            }

        }
    }
    Rectangle{    //皮肤图标
        id: skin
        height: 2/3 * parent.height
        width: 1/15 * parent.width
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: list.left
        anchors.rightMargin: 15
        color: "#F5F5F5"
        Image {
            id: skinicon
            height: 25
            width: 25
            opacity: skinmousearea.containsMouse ? 1.0 : 0.5
            anchors.horizontalCenter: skin.horizontalCenter
            anchors.verticalCenter: skin.verticalCenter
            source: "qrc:/image/TopArea/skin.png"
            MouseArea{
                id:skinmousearea
                anchors.fill: parent
                hoverEnabled: true
            }
        }
    }
    Rectangle{    //刷新图标
        id: renew
        height: 2/3 * parent.height
        width: 1/15 * parent.width
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: skin.left
        anchors.rightMargin: 15
        color: "#F5F5F5"
        Image {
            id: renewicon
            height: 25
            width: 25
            opacity: renewmousearea.containsMouse ? 1.0 : 0.5
            anchors.horizontalCenter: renew.horizontalCenter
            anchors.verticalCenter: renew.verticalCenter
            source: "qrc:/image/TopArea/refresh.png"
            MouseArea{
                id:renewmousearea
                anchors.fill: parent
                hoverEnabled: true
                onClicked: {
                    middleArea.middleface.showPage.visible = false
                    middleArea.refersh.visible = true
                    middleArea.startTimer.start()
                }
            }
        }
    }


    Rectangle{    //登录图标
        id: login
        height: 7/8 * parent.height
        width: 1/10 * parent.width
        radius: 20
        anchors.right: renew.left
        anchors.rightMargin: 15
        anchors.verticalCenter: parent.verticalCenter
        property alias loginIcon:loginIcon
        Image {
            id: loginIcon
            width: parent.width
            height: parent.height
            opacity: loginmousearea.containsMouse ? 1.0 : 0.5
            anchors.horizontalCenter: login.horizontalCenter
            anchors.verticalCenter: login.verticalCenter
            source: "qrc:/image/TopArea/person.png"
            MouseArea{
                id:loginmousearea
                anchors.fill: parent
                hoverEnabled: true
                onClicked: {
                    if(loginstatus === false){
                        audienceItem.open()
                    }else if(loginstatus === true){
                        audienceItem.close()
                        middleArea.audienceInterface.visible =
                                !middleArea.audienceInterface.visible
                    }
                }
            }
        }
    }

}
