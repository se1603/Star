import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2

ScrollView {
    id: sendM_view
    anchors.fill: parent
    clip: true

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
            border.color: "green"
            Text {
                text: modelData
                width: parent.width
                wrapMode: Text.Wrap
            }
        }
    }
}
