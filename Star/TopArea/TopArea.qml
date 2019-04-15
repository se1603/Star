import QtQuick 2.0

Rectangle{
    id:toparea
    width: parent.width
    height: 1/18 * parent.height
    anchors.top: parent.top
    color: "#FFFFFF"
    z:1
    Rectangle{
        id:icon
        width: 1/14 * parent.width
        height: parent.height
        color: "lightblue"
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
    }
    Rectangle{
        id:mainpage
        width: 1/16 * parent.width
        height: parent.height
        anchors.left: icon.right
        anchors.leftMargin: 10
        anchors.verticalCenter: parent.verticalCenter
        z:1
        color: "white"
        Text {
            id: mainpagetitle
            text: qsTr("主页")
            font.pixelSize: 24
            color: "black"
            anchors.horizontalCenter: mainpage.horizontalCenter
            anchors.verticalCenter: mainpage.verticalCenter
        }
        MouseArea{
            id: mainpagemousearea
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
                mainpage.color  = "lightblue"
                mainpagetitle.color = "white"
             //   play.color = "white"
            }
        }
    }
    //点击按钮，跳转到播放页面
    Rectangle{
        id:play
        width: 1/16 * parent.width
        height: parent.height
        anchors.left: mainpage.right
        anchors.leftMargin: 0
        anchors.verticalCenter: parent.verticalCenter
        anchors.topMargin: 0
        z:1
        color: "white"
        Text {
            id: playTitle
            text: qsTr("播放")
            font.pixelSize: 24
            color: "black"
            anchors.horizontalCenter: play.horizontalCenter
            anchors.verticalCenter: play.verticalCenter
        }
        MouseArea{
            id: playpagemousearea
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
                play.color = "lightblue"
                playTitle.color = "white"
            }
        }
    }
    TopSearch { //搜索框
        id:topSearch
    }
    RightButton {  //右边按钮组件
        id:rightButton
    }

}
