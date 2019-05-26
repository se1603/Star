import QtQuick 2.0
import QtQuick.Controls 2.2
import Qt.labs.folderlistmodel 2.2

Popup {
    id: root
    width: 1 / 3 * mainWindow.width
    height: 1 / 2 * mainWindow.height

    x: 1 / 2 * (mainWindow.width - root.width)
    y: 1 / 5 * mainWindow.height

    property string folderPathName:"qrc:///image/avatar"
    property string changePathName
    property string updateFileSource

    Rectangle {
        id: folderRec
        width: parent.width
        height: 3 / 4 * parent.height

        FolderListModel
        {
            id:folderModel
            folder:folderPathName
            showDirs: true
            showFiles: true
            showDirsFirst: true
            showDotAndDotDot: false
            nameFilters: ["*.jpg","*.png","*.jpeg"]
            showOnlyReadable: true
            sortField: FolderListModel.Type
        }

        Component {
            id: fileDelegate

            Rectangle {
                width: 1 / 3 * folderRec.width
                height: 1 / 3 * folderRec.width
                Image {
                    width: parent.width
                    height: parent.height
                    source: "../image/avatar/"+fileName
                    MouseArea {
                        anchors.fill: parent
                        hoverEnabled: true
                        onEntered: {
                            parent.opacity = 0.7
                        }
                        onExited: {
                            parent.opacity = 1
                        }
                        onClicked: {
                            if(folderModel.isFolder(index) === true){
                                changePathName = folderPathName
                                folderPathName =  changePathName + "/" + parent.text
                                folderModel.folder = folderPathName
                            }else{
                                updateFileSource = parent.source
                                choose_title.text = "确定上传 "+fileName+" 吗？"
                            }
                        }
                    }
                }
            }
        }
    }

    ListView {
        width: parent.width
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 1 / 6 * parent.height
        spacing: 10
        model: folderModel
        delegate: fileDelegate
        clip: true
    }


    Rectangle {
        id: chooseRec
        width: parent.width
        height: 1 / 4 * parent.height
        anchors.top: folderRec.bottom
        border.color: "gray"

        Column {
            spacing: 1 / 6 * parent.height
            anchors.centerIn: parent

            Text {
                id: choose_title
                text:"请选择要上传的图片："
                font.pixelSize: 12
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Row {
                spacing: 1 / 3 * chooseRec.height
                Button {
                    text:"确认上传"
                    onClicked: {
                        if(updateFileSource === ""){
                            choose_title.text = "没有选择文件！"
                        }else{
                            client.updateAvatar(updateFileSource,audienceInterface.audienceName)
                        }
                    }
                }
                Button {
                    text:"关闭窗口"
                    onClicked: {
                        choose_title.text = "请选择要上传的图片："
                        updateFileSource = ""
                        dir.close()
                    }
                }
            }
        }
    }

    Connections {
        target: client
        onUpdateAvatarFailed: {
            choose_title.text = "上传失败"
        }
        onUpdateAvatarSucceed: {
            choose_title.text = "上传成功"
            audienceInterface.audienceAvatar = newsource
        }
    }
}
