import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2

Rectangle {
    id:middleMenu

    width: 1/14*parent.width
    height: parent.height

//    border.color: "grey"

    ListView{
        anchors.top:parent.top
        anchors.topMargin: 20
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        model: mainModel
        delegate: mainDelegate
    }

    Component{
        id:mainDelegate
        Rectangle {
            width: middleMenu.width - 10
            height : 1 / 10 * middleMenu.height
            anchors.left: parent.left
//            anchors.leftMargin: 5
            Text {
                text:toolBar
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

    ListModel{
        id:mainModel
        ListElement{
            toolBar:"精选"
        }
        ListElement{
            toolBar:"动漫"
        }
        ListElement{
            toolBar:"电影"
        }
        ListElement{
            toolBar:"剧集"
        }
        ListElement{
            toolBar:"综艺"
        }

    }

    function load_page(page){
        switch(page){
        case '动漫':
            middle_stack.push(comic_page,StackView.Immediate)
            break
        case '电影':
            middle_stack.push(movie_page,StackView.Immediate)
            break
        case '剧集':
            middle_stack.push(drama_page,StackView.Immediate)
            break
        case '综艺':
            middle_stack.push(variety_page,StackView.Immediate)
            break
        case '精选':
            middle_stack.push(select_page,StackView.Immediate)
            break
        }
    }
}
