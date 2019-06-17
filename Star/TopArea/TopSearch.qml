import QtQuick 2.0

Item{
    id:medialButton
    height: parent.height
    width: 1/3 * parent.width
    anchors.left: play.right
    anchors.leftMargin: 1/7 * parent.width
    anchors.verticalCenter: parent.verticalCenter
    visible: true
    signal search

    property var searchList: []     //存放读取的影视资源
    property string text: searchEdit.text
    property alias searchText: searchEdit.text
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
        TextEdit{    //输入文本框
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
                    text = ""
                    topSearch.border.color = "lightblue"
                }
            }
            onTextChanged: {
                text = searchEdit.text   //text为搜索框的输入内容
//                console.log(text)
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
                hoverEnabled: true
                onClicked: {
                      if (text === "") {   //跳转到错误提示页面
                        interfaceS.falsetip.visible = true
                        interfaceS.main.visible = false
                        topArea.visible = true
                        mainMenu.visible = true
                    } else {            //跳转到搜索结果显示页面
                        interfaceS.main.visible = false
                        topArea.visible = false
                        mainMenu.visible = false
                        interfaceS.search.visible = true
                        searchCategory(text)
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
            width: 25
            height: 25
            opacity: recordmousearea.containsMouse ? 1.0 : 0.5
            anchors.horizontalCenter: record.horizontalCenter
            anchors.verticalCenter: record.verticalCenter
            source: "qrc:/image/TopArea/history.png"

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

    function searchCategory(text) {    //实现输入内容与categorys内容匹配，并存入数组  2019.1.3
                                       //修改函数，实现预定匹配功能  2019.1.6

        for (var i = 0; i <= categorys[0].movies.length; i++){
            if (text === categorys[0].movies[i].name){    //全文本匹配成功显示搜索结果，单字搜索匹配未实现
                var tmp
                tmp = categorys[0].movies[i]
                searchList.push(tmp)
                interfaceS.search.movie = searchList
            }
        }
    }

} //medialButton
