import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2

ScrollView {
    id: sendM_view
    anchors.fill: parent
    clip: true

    Text {
        id: notice
        text: "——暂时还没有发送任何消息——"
        font.pixelSize: 26
        color:"#696969"
        anchors.top: parent.top
        anchors.topMargin: 2 / 5 * audienceDisplay.height
        anchors.left: parent.left
        anchors.leftMargin: 1 / 3 * audienceDisplay.width
        visible:sendM.length === 0 ? true : false
    }

    ListView {
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        model: sendM
        delegate: send_delegate
    }

    Component {
        id: send_delegate
        Rectangle {
            width: sendM_view.width
            height: 1 / 7 * sendM_view.height
            Text {
                text: modelData
                width: parent.width
                wrapMode: Text.Wrap
            }
        }
    }
}
