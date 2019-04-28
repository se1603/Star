import QtQuick 2.0

Item {
    Rectangle{

        width: 100
        height: parent.height
        color: "red"
        anchors.right:parent.right
    }
    Text{
        id:f
        anchors.centerIn: parent
        text: "COMIC"
        font.pixelSize: 32
    }
}
