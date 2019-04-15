import QtQuick 2.0

Item {
    id:rightButton
    width: 1/3 * parent.width
    height: parent.height
    anchors.right: parent.right
    anchors.rightMargin: 5
    anchors.verticalCenter: parent.verticalCenter
    visible: true
    Rectangle{     //菜单图标
        id: list
        height: 2/3 * parent.height
        width: 1/15 * parent.width
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        Image {
            id: listicon
            width: 20
            height: 20
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
    }
    Rectangle{    //皮肤图标
        id: skin
        height: 2/3 * parent.height
        width: 1/15 * parent.width
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: list.left
        anchors.rightMargin: 10
        Image {
            id: skinicon
            height: 20
            width: 20
            opacity: skinmousearea.containsMouse ? 1.0 : 0.5
            anchors.horizontalCenter: skin.horizontalCenter
            anchors.verticalCenter: skin.verticalCenter
            source: "qrc:/image/TopArea/skin.jpg"
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
        anchors.rightMargin: 10
        Image {
            id: renewicon
            height: 20
            width: 20
            opacity: renewmousearea.containsMouse ? 1.0 : 0.5
            anchors.horizontalCenter: renew.horizontalCenter
            anchors.verticalCenter: renew.verticalCenter
            source: "qrc:/image/TopArea/renew.jpg"
            MouseArea{
                id:renewmousearea
                anchors.fill: parent
                hoverEnabled: true
            }
        }
    }
    Rectangle{    //登录图标
        id: login
        height: 7/8 * parent.height
        width: 1/10 * parent.width
        radius: 20
        anchors.right: renew.left
        anchors.rightMargin: 10
        anchors.verticalCenter: parent.verticalCenter
        color: "lightgray"
        Image {
            id: loginIcon
            opacity: loginmousearea.containsMouse ? 1.0 : 0.5
            anchors.horizontalCenter: login.horizontalCenter
            anchors.verticalCenter: login.verticalCenter
            source: "qrc:/image/TopArea/user.png"
            MouseArea{
                id:loginmousearea
                anchors.fill: parent
                hoverEnabled: true
            }
        }
    }

}
