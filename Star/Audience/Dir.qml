import QtQuick 2.0
import QtQuick.Controls 2.2
import Qt.labs.folderlistmodel 2.2

Popup {
    id: root
    width: 1 / 3 * mainWindow.width
    height: 1 / 2 * mainWindow.height

    x: 1 / 2 * (mainWindow.width - root.width)
    y: 1 / 5 * mainWindow.height

    property string folderPathName:"file:///root"
    property string changePathName
    property string updateFileName

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
            showDotAndDotDot: root
            nameFilters: ["*.jpg","*.png"]
            showOnlyReadable: true
            sortField: FolderListModel.Type
        }

        Component {
            id: fileDelegate

            Text {
                text: fileName
                color: folderModel.isFolder(index) ? "green" : "black"
                font.pixelSize: 15
                opacity: 0.5
                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    onEntered: {
                        parent.opacity = 1
                    }
                    onExited: {
                        parent.opacity = 0.7
                    }
                    onClicked: {
                        if(folderModel.isFolder(index) === true){
                            changePathName = folderPathName
                            folderPathName =  changePathName + "/" + parent.text
                            folderModel.folder = folderPathName
                        }else{
                            updateFileName = parent.text
                            choose_title.text = "确定上传 "+updateFileName+" 吗？"
                        }
                    }
                }
            }
        }

        ListView {
            width: parent.width
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 1 / 50 * parent.height
            model: folderModel
            delegate: fileDelegate
        }
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
                        if(updateFileName === ""){
                            choose_title.text = "没有选择文件！"
                        }else{
                            choose_title.text = "正在上传…"
                            var filestring = folderPathName + "/" + updateFileName
                            client.updateAvatar(filestring,audienceInterface.audienceName)
                        }
                    }
                }
                Button {
                    text:"取消"
                    onClicked: {
                        choose_title.text = "请选择要上传的图片："
                        updateFileName = ""
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
    }
}
