import QtQuick 2.0

Rectangle{
    id: none
    height: parent.height
    width: parent.width
    anchors.fill: parent
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
                        if(search_stack.depth > 2) {
                            search_stack.pop()
                        } else {
                            middle_stack.pop(select_page)
                            middleArea.middleface.search.visible = false
                        }
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
                        middle_stack.pop(select_page)
                        middleArea.middleface.search.visible = false
                    }
                }
            }
        }
    }
    Rectangle{
        id:tips
        width: parent.width
        height: 19/20 * parent.height
        anchors.left: parent.left
        anchors.top: toprectangle.bottom
        Text {
            id: tip
            anchors.centerIn: parent
            font.pixelSize: 45
            color: "#1E90FF"
            text: qsTr("没有找到哟，请再试一次！")
        }
    }
}
