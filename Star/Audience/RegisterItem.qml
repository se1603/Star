import QtQuick 2.0
import QtQuick.Controls 2.2

Page {
    id: registeritem
    width: parent.width
    height: parent.height
    visible: true

    Connections {
        target: client
        onRegistesucceed: {
            noticeText.text = "注册成功"
        }
        onRegistefailed: {
            noticeText.text = "用户名重复，请重新注册"
        }
        onRegisterInfoWrong: {
            noticeText.text = "用户名或密码包含非法字符，请重新输入"
        }
    }

    Column {
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 1 / 24 * register.height

        Text {
            id:titleText
            text: "注册"
            font.pixelSize: 25
            font.family: "Times"
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Row {
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 1 / 30 * register.height
            Column {
                anchors.top: parent.top
                anchors.topMargin: 5
                spacing: 1 / 9 * login.height

                Text {
                    text: "用户名："
                    font.pixelSize: 20
                }

                Text {
                    text: "密码："
                    font.pixelSize: 20
                }

                Text {
                    text: "确认密码："
                    font.pixelSize: 20
                }
            }

            Column {
                spacing: 1 / 9 * register.height

                TextField {
                    id:nameInput
                }

                TextField {
                    id:passwordInput
                    echoMode: TextInput.Password
                }

                TextField {
                    id:passwordReInput
                    echoMode: TextInput.Password
                }
            }
        }

        Text {
            id: noticeText
            text: " "
            color: "red"
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: 12
        }

        Row {
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 1 / 6 * register.height

            Button {
                text: "注册"
                onClicked: {
                    if(nameInput.text === "" || passwordInput.text === "" || passwordReInput.text === ""){
                        noticeText.text = "the content is empty,please input again"
                    }else if(passwordInput.text !== passwordReInput.text){
                        noticeText.text = "两次密码不一致"
                    }else if(passwordInput.text.length < 6 || passwordInput.length > 12){
                        noticeText.text = "密码位数小于6位或大于12位，请重新输入"
                    }else if(nameInput.text.length < 1 || nameInput.text.length > 12){
                        noticeText.text = "名字位数小于12位，请重新输入"
                    }
                    else{
                        noticeText.text = " "
                        console.log(nameInput.text,passwordInput.text)
                        client.sendRegisterInfo(nameInput.text,passwordInput.text)
                    }
                    nameInput.text=""
                    passwordInput.text=""
                    passwordReInput.text=""
                }
            }

            Button {
                text: "返回"
                onClicked: {
                    login.visible = !login.visible;
                    register.visible = !register.visible
                    nameInput.text=""
                    passwordInput.text=""
                }
            }
        }
    }
}
