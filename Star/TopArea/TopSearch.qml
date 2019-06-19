import QtQuick 2.0
import "../MiddleArea"

Item{
    id:medialButton
    height: parent.height
    width: 1/3 * parent.width
    anchors.left: play.right
    anchors.leftMargin: 1/7 * parent.width
    anchors.verticalCenter: parent.verticalCenter
    visible: true
    //signal search

    property var searchtext
    property var searchcount
    property string text: searchEdit.text

    property var temp

    //search输入框

    Rectangle{
        id:topSearch
        width:3/4 * parent.width
        height: 3/4 * parent.height
        radius:15
        border.width: 2
        border.color: "lightgray"
        anchors.left: medialButton.left
        anchors.verticalCenter: medialButton.verticalCenter
        color:"white"
        TextInput{    //输入文本框
            id:searchEdit
            width: parent.width
            height: parent.height
            anchors.left: parent.left
            anchors.leftMargin: 15
            anchors.verticalCenter: topSearch.verticalCenter
            selectByMouse: true
            font.pixelSize: 18
            color: "black"
            opacity: 0.5
            focus: false
            onFocusChanged: {
                if (focus == true){
                    topSearch.border.color = "lightblue"
                }
            }
            onAccepted: {
                temp = JSON.parse(client.search(text))
                if(temp[0].type === "Film"){
                    middleArea.middleface.searchMovie = temp
                    middleArea.middleface.search.visible = true
                    middleArea.middleface.search.searchPage(temp[0].type)
                }
                else if(temp[0].type === "Drama"){
                    middleArea.middleface.searchDrama = temp
                    middleArea.middleface.search.visible = true
                    middleArea.middleface.search.searchPage(temp[0].type)
                }
                else if(temp[0].type === "Comic"){
                    middleArea.middleface.searchDrama = temp
                    middleArea.middleface.search.visible = true
                    middleArea.middleface.search.searchPage(temp[0].type)
                }
                else if(temp[0].type === "Actor"){
                    middleArea.middleface.searchCharacter = temp;
                    middleArea.middleface.search.visible = true
                    middleArea.middleface.search.searchPage(temp[0].type)
                }
                else if(temp[0].type === "Director"){
                    middleArea.middleface.searchCharacter = temp;
                    middleArea.middleface.search.visible = true
                    middleArea.middleface.search.searchPage(temp[0].type)
                }
            }
        }

        Image {  //搜索图标
            id: searchicon
            height: 20
            width: 20
            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            opacity: searchmousearea.containsMouse ? 1.0 : 0.5
            source: "qrc:/image/TopArea/search.png"
            MouseArea{
                id: searchmousearea
                anchors.fill: parent
                acceptedButtons: Qt.LeftButton | Qt.RightButton
                hoverEnabled: true
                onClicked: {
                    temp = JSON.parse(client.search(text))
                    if(temp[0].type === "Film"){
                        middleArea.middleface.searchMovie = temp
                        middleArea.middleface.search.visible = true
                        middleArea.middleface.search.searchPage(temp[0].type)
                    }
                    else if(temp[0].type === "Drama"){
                        middleArea.middleface.searchDrama = temp
                        middleArea.middleface.search.visible = true
                        middleArea.middleface.search.searchPage(temp[0].type)
                    }
                    else if(temp[0].type === "Comic"){
                        middleArea.middleface.searchDrame = temp
                        middleArea.middleface.search.visible = true
                        middleArea.middleface.search.searchPage(temp[0].type)
                    }
                    else if(temp[0].type === "Actor"){
                        middleArea.middleface.searchCharacter = temp;
                        middleArea.middleface.search.visible = true
                        middleArea.middleface.search.searchPage(temp[0].type)
                    }
                    else if(temp[0].type === "Director"){
                        middleArea.middleface.searchCharacter = temp;
                        middleArea.middleface.search.visible = true
                        middleArea.middleface.search.searchPage(temp[0].type)
                    }
                }
            }
        }
    }
    //历史记录图标
    Rectangle{
        id:record
        width: 30
        height: 30
        anchors.left: topSearch.right
        anchors.leftMargin: 2
        anchors.verticalCenter: parent.verticalCenter
        color: "#F5F5F5"
        Image {
            id: recordicon
            height: 25
            width: 25
            opacity: recordmousearea.containsMouse ? 1.0 : 0.5
            anchors.horizontalCenter: record.horizontalCenter
            anchors.verticalCenter: record.verticalCenter
            source: "qrc:/image/TopArea/history.png"
            MouseArea{
                id:recordmousearea
                anchors.fill: parent
                hoverEnabled: true
                onClicked: {
                    if(middleArea.audienceInterface.audienceName !== ""){
                        middleArea.middleface.browse_records = JSON.parse(
                                    client.audienceRecord(middleArea.audienceInterface.audienceName))
                    }else{
                        middleArea.middleface.browse_records = JSON.parse(
                                    client.browseRecord())
                    }
                    middleArea.middleface.middleStack.push(middleArea.middleface.recordPage)
                    middleArea.playInterface.visible = false
                    middleArea.audienceInterface.visible = false
                    middleArea.middleface.visible = true
                }
            }
        }
    }
} //medialButton
