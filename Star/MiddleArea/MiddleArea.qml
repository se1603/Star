import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import "../Audience"


Rectangle {
    id:middlearea
    width: parent.width
    height: 17/18 * parent.height
    //   color:"gray"
    anchors.bottom: parent.bottom

    MiddleInterface{
        id:middle_face
    }

    property alias audienceInterface:audienceInterface

    AudienceInterface {
        id: audienceInterface
        visible: false
    }
}
