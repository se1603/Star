import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import "../Audience"
import "../PlayArea"

Rectangle {
    id:middlearea
    width: parent.width
    height: 17/18 * parent.height
    //   color:"gray"
    anchors.bottom: parent.bottom

    property alias audienceInterface:audienceInterface
    property alias play:play.visible
    property alias middle:middle_face.visible



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
