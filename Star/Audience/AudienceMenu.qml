import QtQuick 2.0
import QtQuick.Controls 2.2

Rectangle {
    id: audience_menu
    width: 8 / 60 * parent.width
    height: parent.height
    border.color: "gray"

    Column {
        width: parent.width
        height: parent.height
        spacing: 25
        anchors.top: parent.top
        anchors.topMargin: 10

        Rectangle {
            id: audience_avator
            width: 1 / 6 * parent.height
            height: 1 / 6 * parent.height
            radius: 1 / 2 * audience_avator.width
            border.color: "gray"
            anchors.horizontalCenter: parent.horizontalCenter

            MouseArea {
                anchors.fill:parent
                onClicked: dir.open()
            }

            Image {
                width: 2 / 3 * parent.width
                height: 2 / 3 * parent.height
                source:"../image/audience/头像.jpg"
                anchors.centerIn: parent
            }
        }

        Text {
            id:audience_name
            text: audienceInterface.audienceName
            font.pixelSize: 35
            font.family: "Beta Dance"
            anchors.horizontalCenter: parent.horizontalCenter
        }

        ListView {
            anchors.top: audience_name.bottom
            anchors.topMargin: 100
            anchors.bottom: parent.bottom
            model: audience_choice
            delegate: audience_delegate
        }

    }

    Component {
        id:audience_delegate
        Rectangle {
            width: audience_menu.width - 10
            height : 1 / 10 * audience_menu.height
            anchors.left: parent.left
            anchors.leftMargin: 5
            Text {
                text:name
                opacity: 0.5
                font.pixelSize: 15
                anchors.horizontalCenter: parent.horizontalCenter
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
                        load_page(parent.text)
                    }
                }
            }
        }
    }

    ListModel {
        id:audience_choice
        ListElement {
            name: "收藏"
        }
        ListElement {
            name: "浏览历史"
        }
        ListElement {
            name: "消息"
        }
        ListElement {
            name: ""
        }
        ListElement {
            name: "退出"
        }
    }

    function load_page(page) {
        switch (page) {
        case '收藏':
            audience_stack.push(collection_page,StackView.Immediate)
            break
        case '浏览历史':
            audience_stack.push(record_page,StackView.Immediate)
            break
        case '消息':
            audience_stack.push(message_page,StackView.Immediate)
            break
        case '退出':{
            client.loginOut(audience_name.text)
            middleArea.audienceInterface.visible = false
            }
        }
    }

    Dir {
        id: dir
    }
}
