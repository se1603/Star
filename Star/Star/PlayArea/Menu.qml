import QtQuick 2.0
import QtQuick.Controls 2.0
Rectangle {
    id:menu
    width: parent.width
    height: 2/17*parent.height
    anchors.top:parent.top
    anchors.left: parent.left
    anchors.right: parent.right

    color: "gray"
    border.color: "red"

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
        }
    }
}
