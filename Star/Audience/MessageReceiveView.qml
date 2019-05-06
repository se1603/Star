import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2

ScrollView {
    id: receiveM_view
    anchors.fill: parent
    clip: true

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
            border.color: "green"
            Text {
                text: modelData
                width: parent.width
                wrapMode: Text.Wrap
            }
        }
    }
}
