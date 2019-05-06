import QtQuick 2.0
import "TopArea"
import "MiddleArea"
import "Audience"

Rectangle {
    width: parent.width
    height: parent.height

    property alias middleArea:middleArea

    TopArea{
        id: topArea
        visible: true
    }

    MiddleArea {
        id:middleArea
        visible:visible
    }

    AudiencePoupItem {
        id:audienceItem
    }
}
