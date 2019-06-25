import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2

ScrollView {
    id: receiveM_view
    anchors.fill: parent
    clip: true

    Text {
        id: notice
        text: "——暂时还没有收到任何消息——"
        font.pixelSize: 26
        color:"#696969"
        anchors.top: parent.top
        anchors.topMargin: 2 / 5 * audienceDisplay.height
        anchors.left: parent.left
        anchors.leftMargin: 1 / 3 * audienceDisplay.width
        visible:receiveM.length === 0 ? true : false
    }

    ListView {
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        model: receiveM
        delegate: receive_delegate
    }

    Component {
        id: receive_delegate
        Rectangle {
            width: receiveM_view.width
            height: 1 / 7 * receiveM_view.height
            Text {
                text: modelData
                width: parent.width
                wrapMode: Text.Wrap
            }
        }
    }
}
