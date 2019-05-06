import QtQuick 2.0

Rectangle {
    width: 160
    height: 160
    border.color: "red"
    Rectangle {
        id: collection_img
        width: parent.width
        height: 120
        border.color : "green"
    }
    Text {
        id: collection_text
        width: parent.width
        text: modelData
        wrapMode: Text.Wrap
        anchors.top: collection_img.bottom
    }
}
