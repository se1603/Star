import QtQuick 2.0
import QtQuick.Controls 2.2
import "../MiddleArea"

Page {
    id: loginitem
    width: parent.width
    height: parent.height
    visible: true

    Connections {
        target: client
        onLoginsucceed : {
            topArea.rightButton.loginPic.loginIcon.source = avatar
            topArea.rightButton.loginstatus = true
            middleArea.audienceInterface.audienceName = name
            middleArea.audienceInterface.audienceAvatar = avatar
            audienceItem.close()
        }
        onLoginfailed: {
            noticeText.text = "name or password is not correct,please input again"
        }
        onLoginout: {
            topArea.rightButton.loginPic.loginIcon.source = "qrc:/image/TopArea/user.png"
            topArea.rightButton.loginstatus = false
            middleArea.audienceInterface.visible = false
        }
        onHaslogined: {
            noticeText.text = "this account has logined!"
        }
    }

    Column {
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 1 / 12 * login.height

        Text {
            id:titleText
            text: "登录"
            font.pixelSize: 25
            font.family: "Times"
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Row {
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 1 / 30 * login.width
            Column {
                anchors.top: parent.top
                anchors.topMargin: 5
                spacing: 1 / 5 * login.height

                Text {
                    text: "用户名："
                    font.pixelSize: 20
                }

                Text {
                    text: "密码："
                    font.pixelSize: 20
                }
            }

            Column {
                spacing: 1 / 6 * login.height

                TextField {
                    id:nameInput
                }

                TextField {
                    id:passwordInput
                    echoMode: TextInput.Password
                }
            }
        }

        Text {
            id: registerText
            anchors.horizontalCenter: parent.horizontalCenter

            text:"没有帐号？点击这里注册"
            opacity: 0.5
            font.pixelSize: 16

            MouseArea {
                anchors.fill: parent
                enabled: true
                hoverEnabled: true
                acceptedButtons: Qt.LeftButton | Qt.RightButton
                onEntered: {
                    parent.opacity = 1
                }
                onExited: {
                    parent.opacity = 0.5
                }
                onClicked: {
                    noticeText.text = ""
                    login.visible = !login.visible;
                    register.visible = !register.visible
                }
            }
        }

        Text {
            id: noticeText
            text: ""
            color: "red"
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: 12
            anchors.top: registerText.bottom
        }

        Row {
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 1 / 12 * login.width

            Button {
                text: "登录"
                onClicked: {
                    if(nameInput.text ==="" || passwordInput.text === ""){
                        noticeText.text = "the content is empty,please input again"
                    }else{
                        noticeText.text = ""
                        client.sendLoginInfo(nameInput.text,passwordInput.text)
                    }
                    nameInput.text=""
                    passwordInput.text=""
                }
            }

            Button {
                text: "关闭"
                onClicked: {
                    noticeText.text = ""
                    nameInput.text=""
                    passwordInput.text=""
                    audienceItem.close()
                }
            }
        }
    }
}
