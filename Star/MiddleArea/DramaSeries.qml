import QtQuick 2.0

Item {
    Rectangle{
        id:rec
        width: parent.width
        height: parent.height
        anchors.top: parent.top
        color: "lightblue"
    }
    Text {
        id: name
        text: qsTr("Drama Series")
        anchors.top:rec.bottom
    }
}
