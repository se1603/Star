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
    }

    Column {
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 1 / 12 * register.height

        Text {
            id:titleText
            text: "注册"
            font.pixelSize: 25
            font.family: "Times"
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Row {
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 1 / 12 * register.height
            Column {
                spacing: 1 / 6 * register.height

                Text {
                    text: "用户名："
                    font.family: "Times"
                    font.pixelSize: 20
                }

                Text {
                    text: "密码："
                    font.family: "Times"
                    font.pixelSize: 20
                }
            }

            Column {
                spacing: 1 / 6 * register.height

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
                    if(nameInput.text === "" || passwordInput.text === ""){
                        noticeText.text = "the content is empty,please input again"
                    }else{
                        noticeText.text = " "
                        console.log(nameInput.text,passwordInput.text)
                        client.sendRegisterInfo(nameInput.text,passwordInput.text)
                    }
                    nameInput.text=""
                    passwordInput.text=""
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
