import QtQuick 2.0
import "TopArea"
import "MiddleArea"
import "Audience"
import "PlayArea"

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
    }

    AudiencePoupItem {
        id:audienceItem
    }

    function fullScreen(){
        topArea.visible = false
        topArea.z = -1
        fullScreenFlag = false
    }

    function exitfullScreen(){
        topArea.visible = true
        topArea.z = 1
        fullScreenFlag = true
    }

}
