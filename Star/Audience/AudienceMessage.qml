import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Rectangle {
    id: message_part
    width: 59 / 60 * audienceDisplay.width
    height: 59 / 60 * audienceDisplay.height
    border.color: "gray"

    property var receiveM
    property var sendM


    Row {
        id: message_bar
        width: parent.width
        anchors.top: parent.top
        anchors.topMargin: 1 / 50 * parent.height
        anchors.left: parent.left
        anchors.leftMargin: 1 / 50 * parent.width
        spacing: 1 / 50 * parent.width
        Text {
            id: message_receiveButton
            text: "我收到的消息"
            font.pixelSize: 15
            opacity: 0.7
            color: "green"
            MouseArea {
                anchors.fill: parent
                acceptedButtons: Qt.RightButton | Qt.LeftButton
                hoverEnabled: true
                enabled: true

                onEntered: {
                    parent.opacity = 1
                }
                onExited: {
                    parent.opacity = 0.5
                }
                onClicked: {
                    message_stack.push(message_receive,StackView.Immediate)
                    parent.color = "green"
                    message_sendButton.color = "black"
                }
            }
        }
        Text {
            text: "|"
            font.pixelSize: 15
            opacity: 0.7
        }
        Text {
            id: message_sendButton
            text: "我发送的消息"
            font.pixelSize: 15
            opacity: 0.7
            MouseArea {
                anchors.fill: parent
                acceptedButtons: Qt.RightButton | Qt.LeftButton
                hoverEnabled: true
                enabled: true

                onEntered: {
                    parent.opacity = 1
                }
                onExited: {
                    parent.opacity = 0.5
                }
                onClicked: {
                    message_stack.push(message_send,StackView.Immediate)
                    parent.color = "green"
                    message_receiveButton.color = "black"
                }
            }
        }
    }

    Rectangle {
        id: message_rec
        width: 49 / 50 * parent.width
        height: 49 / 50 * parent.height - message_bar.height
        anchors.left: parent.left
        anchors.leftMargin: 1 / 100 * parent.width
        anchors.top: message_bar.bottom
        anchors.bottom: parent.bottom
        StackView {
            id: message_stack
            anchors {
                top: parent.top
                bottom: parent.bottom
                fill: parent
            }
            initialItem: message_receive
        }
    }


    Component {
        id: message_receive
        MessageReceiveView{
        }
    }
    Component {
        id: message_send
        MessageSendView{
        }
    }
}
