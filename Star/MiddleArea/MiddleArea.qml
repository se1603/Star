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

    property var playingName:""
    property var startTime:""
    property var duration:""
    property var videoType:""

    property var playRtspUrl: ""

    property alias refersh: refersh
    property alias startTimer: startTimer


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

    Timer{
        id:startTimer
        interval: 1000
        running: false
        onTriggered: {
            refershComplete.visible = true
            refersh.visible = false
            middleface.showPage.visible = true
            stopTimer.start()
        }
    }

    Timer{
        id:stopTimer
        interval: 1000
        running: false
        onTriggered: {
            refershComplete.visible = false
        }
    }

    Rectangle{
        id:refersh
        visible: false
        color: "#C0C0C0"
        width: 100
        height: 30
        radius: 20
        anchors.top: topArea.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        Text {
            text: "正在刷新..."
            color: "white"
            anchors.centerIn: parent
            font.pixelSize: 16
        }
    }

    Rectangle{
        id:refershComplete
        visible: false
        color: "#C0C0C0"
        width: 120
        height: 30
        radius: 20
        anchors.top: topArea.bottom
        anchors.horizontalCenter: parent.horizontalCenter

        Text {
            text: "已刷新到最新"
            color: "white"
            anchors.centerIn: parent
            font.pixelSize: 16
        }
    }
}
