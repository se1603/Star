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
                middleArea.middleface.searchMovie = JSON.parse(client.search(text)) //text为搜索框的输入内容
                middleArea.middleface.middlemenu.load_page(1)
//                console.log("aaaaa")
//                console.log(text)
//                console.log(middleArea.middleface.searchMovie)
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
                    middleArea.middleface.searchMovie = JSON.parse(client.search(searchEdit.text))
                    middleArea.middleface.middlemenu.load_page(1)
//                    console.log(text)
//                    console.log(middleArea.middleface.searchMovie)  //searchMovie已存入内容
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
        Image {
            id: recordicon
            height: 20
            width: 20
            opacity: recordmousearea.containsMouse ? 1.0 : 0.5
            anchors.horizontalCenter: record.horizontalCenter
            anchors.verticalCenter: record.verticalCenter
            source: "qrc:/image/TopArea/timg.jpg"
            MouseArea{
                id:recordmousearea
                anchors.fill: parent
                hoverEnabled: true
                onClicked: {
                    RecordPage.visible = true
                }
            }
        }
    }
//    ListModel{
//        id:searchMovieModel
//    }

//    function searchKeys(searchtext){
//        var key = searchtext
//        var a = key.split(",")
//        console.log(a)
//        searchMovieModel.clear()
//        for(var i = 0; i < key.size(); i++){
//            searchMovieModel.append({
//                                        name:key[i].name,
//                                        post:key[i].post,
//                                    })
//        }
//    }
} //medialButton
