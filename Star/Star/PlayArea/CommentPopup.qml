import QtQuick 2.0
import QtQuick.Controls 2.2

Popup {
    id:pop
    width: parent.width
    height: parent.height

    background:  Rectangle{
        width: parent.width
        height: parent.height
        color: "#8B8378"
    }

    x:0
    y:0

    Text{
        width:parent.width
        wrapMode: Text.Wrap
        text: "你还没有登录，请登录后评论"
    }
}
