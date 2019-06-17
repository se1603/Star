import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5
import "../Audience"
import "../PlayArea"

Rectangle {
    id:middlearea
    width: parent.width
    height: fullScreenFlag ?  17/18 * parent.height : parent.height
    //       color:"red"
    anchors.bottom: parent.bottom
    //    anchors.top: topArea.bottom

    property alias audienceInterface:audienceInterface
    property alias play:play.visible
    property alias middle:middle_face.visible
    property alias middleface: middle_face

    property alias playInterface: play


//    SwipeView{
//        id: view

//        currentIndex: 0
//        anchors.fill: parent

//        MiddleInterface{
//            id:middle_face
//        }

//        Play{
//            id:play
//        }

//    }

    MiddleInterface{
        id:middle_face
    }

    Play{
        id:play
        visible: false
    }


    AudienceInterface {
        id: audienceInterface
        visible: false
    }
}
