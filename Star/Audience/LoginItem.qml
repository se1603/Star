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
            topArea.rightButton.loginPic.loginIcon.source = "../image/audience/头像.jpg"
            topArea.rightButton.loginstatus = true
            audienceItem.close()
            middleArea.audienceInterface.audienceName = client.getMyaudience()
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

    Image {
        width: parent.width
        height: parent.height
        source: "../image/audience/popup_background.jpg"
        opacity: 0.5
    }

    Column {
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 1 / 12 * login.height

        Text {
            id:titleText
            text: "Login"
            font.pixelSize: 25
            font.family: "Times"
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Row {
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 1 / 10 * login.width
            Column {
                spacing: 1 / 6 * login.height

                Text {
                    text: "Name:"
                    font.family: "Times"
                    font.pixelSize: 20
                }

                Text {
                    text: "Password:"
                    font.family: "Times"
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
                }
            }
        }

        Text {
            id: registerText
            anchors.horizontalCenter: parent.horizontalCenter

            text:"No account? Click this to register"
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
                text: "Login"
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
                text: "Close"
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
