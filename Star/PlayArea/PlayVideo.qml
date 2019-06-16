/*
  Author:王梦娟
  Date:2019-5-25
*/
import QtQuick 2.0
import Star 1.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls 2.5
import QtQuick.Window 2.12

Rectangle {
    id:mainPlay
    width: parent.width
    height: parent.height

    property string path: ""

    property bool noResurce: false

    property bool pauseVideo: false
    property bool playing: false
    property bool firstPlay: false
    property bool stopVideo: false
    property bool isFullScreen: false

    property alias noteRectangle: note

    property var previousWidth: 1075
    property var previousHeight: 670

    //    property alias videoPlayer: player

    Timer{
        id:timer1
        interval: 2000
        running: false
        onTriggered: {
            leftbu.width = 0
            rightbt.width=0
        }
    }

    MouseArea{
        anchors.fill: parent
        hoverEnabled: true
        onEntered: {
            leftbu.width = 20
            rightbt.width = 20
        }
        onExited: {
            timer1.start()
        }
    }

    Rectangle{
        id:rightbt
        y:parent.height/2
        z:3
        anchors.right: parent.right
        width: 20
        height: 30
        opacity: 0.5
        Image{
            id:rightButton
            opacity: 1
            mirror: true
            anchors.fill: parent
            source: "qrc:/image/img/left.png"
        }
        MouseArea{
            id:rightMouse
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
                if(rightRec.x === mainWindow.width){
                    menuStopAnim.start()
                    xflag = true
                }else{
                    menuStartAnim.start()
                    xflag = false
                }
            }
        }
    }

    //左箭头，点击，会回到前一张图片
    Rectangle{
        id:leftbu
        y:parent.height/2
        z:3
        anchors.left: parent.left
        width: 20
        height: 30
        opacity: 0.5
        Image{
            id:leftButton
            anchors.fill: parent
            opacity: 1
            source: "qrc:/image/img/left.png"
        }
        MouseArea{
            id:leftMouse
            anchors.fill: parent
            hoverEnabled: true
            propagateComposedEvents: true
            onClicked: {
                if(leftRect.x === 0){
                    leftStartAnim.start()
                    xRflag = false
                }else{
                    leftStopAnim.start()
                    xRflag = true
                }
            }
        }
    }

    Rectangle{
        id:note
        z:3
        color: "white"
        visible: false
        width: 200
        height: 50
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter

        Text {
            id: noteText
            text: "暂无资源"
            font.pixelSize: 20
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
        }
    }

    Rectangle{
        id: playVideo
        width: parent.width
        height: parent.height
        color: "black"
        VideoPlayer{
            id:player
            anchors.fill: parent
            width: parent.width
            height: parent.height
            vwidth: parent.width
            vheight: parent.height
        }
        MouseArea{
            anchors.fill: parent
            onClicked: {
//                console.log(path)

                if(!firstPlay)
                {
                    player.startPlay(path)
                    playing = true
                    firstPlay = true
                    stopVideo = false
                }
            }
        }
    }

    Connections{
        target: player
        onSigShowTotalTime:
        {
            console.log(player.showTotalTime())
            duation.text = player.showTotalTime()
        }
        onSigShowCurrentTime:
        {
            timing.text = player.showCurrentTime()
        }
        onSigSliderTotalValue:{
            progressBar.to = value
            console.log(progressBar.to)
        }
        onSigSliderValue:{
            progressBar.value = currentvalue
        }
        onNoResource:{
            console.log("收到信号")
            note.visible = true
            noResurce = true
        }
    }

    Rectangle{
        color: "black"
        width: parent.width
        height: parent.height * 1 / 18
        anchors.bottom: parent.bottom
        visible: true

        MouseArea{
            anchors.fill: parent
            hoverEnabled: true

            onEntered:{
                allController.visible = true
            }
            onExited: {
                timer.start()
            }
        }
    }

    Timer{
        id:timer
        interval: 5000;
        running: true;
        repeat: true
        onTriggered:{
            allController.visible = false
        }
    }

    Connections{
        target: progressBar
        onMoved:{
            player.sliderMoved(progressBar.value)
        }
    }

    Rectangle{
        id: allController
        color: "#DDDDDD"
        width: parent.width
        height: parent.height * 1 / 18
        anchors.bottom: parent.bottom
        visible: true

        Slider{
            id:progressBar
            width: parent.width
            height: parent.height * 2 / 5
            anchors.top: parent.top
            from: 0
            to:100
            //            value: 0

            background: Rectangle {
                x: progressBar.leftPadding
                y: progressBar.topPadding + progressBar.availableHeight / 2 - height / 2
                implicitWidth: 200
                implicitHeight: 4
                width: progressBar.availableWidth
                height: implicitHeight
                radius: 2
                color: "#bdbebf"

                Rectangle {
                    width: progressBar.visualPosition * parent.width
                    height: parent.height
                    color: "#00BBFF"
                    radius: 2
                }
            }

            handle: Rectangle{
                x:progressBar.leftPadding + progressBar.visualPosition * (progressBar.availableWidth - width)
                y: progressBar.topPadding + progressBar.availableHeight / 2 - height / 2
                color:progressBar.pressed ? "#00BBFF":"white";
                border.color: "gray";
                width: 15;
                height: 15;
                radius: 12;
            }

        }

        Rectangle{
            id:controller
            //            color: "#DDDDDD"
            width: parent.width
            height: parent.height * 3 / 5
            anchors.top: progressBar.bottom

            Rectangle{
                id:play
                width: parent.height
                height: parent.height
                anchors.left: parent.left
                //                anchors.leftMargin: 10
                //            color: "green"
                Image {
                    width: parent.height
                    height: parent.height
                    anchors.fill: parent
                    source: playing && !noResurce ? "../image/videoController/pause.png" : "../image/videoController/play.png"
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        if(!firstPlay)
                        {
                            player.startPlay(path)
                            playing = true
                            firstPlay = true
                            stopVideo = false
                        }
                        else if(pauseVideo)
                        {
                            player.play()
                            pauseVideo = false
                            playing = true
                        }
                        else if(playing)
                        {
                            player.pause()
                            playing = false
                            pauseVideo = true
                        }
                    }
                }
            }

            Rectangle{
                id:stop
                width: parent.height
                height: parent.height

                anchors.left: play.right
                anchors.leftMargin: 20
                //            color: "green"

                Image {
                    width: parent.height
                    height: parent.height
                    anchors.fill: parent
                    source: "../image/videoController/stop.png"
                }

                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        if(!stopVideo)
                        {
                            stopPlay()
                        }
                    }
                }
            }

            Rectangle{
                id:next
                width: parent.height
                height: parent.height

                anchors.left: stop.right
                anchors.leftMargin: 20
                //            color: "green"
                Image {
                    width: parent.height
                    height: parent.height
                    anchors.fill: parent
                    source: "../image/videoController/next.png"
                }
            }

            Rectangle{
                id:time
                width: 4 * parent.height
                height: parent.height

                anchors.left: next.right
                anchors.leftMargin: 20

                Text {
                    id: timing
                    text: "00:00:00"
                    anchors.verticalCenter: parent.verticalCenter
                }

                Text {
                    id:slash
                    text: " / "
                    anchors.left: timing.right
                    anchors.verticalCenter: parent.verticalCenter
                }

                Text {
                    id: duation
                    text: "00:00:00"
                    anchors.left: slash.right
                    anchors.verticalCenter: parent.verticalCenter
                }
            }

            Rectangle{
                id:fullScreen
                width: parent.height
                height: parent.height

                anchors.right: parent.right
                anchors.rightMargin: 10
                //            color: "green"
                Image {
                    width: parent.height
                    height: parent.height
                    anchors.fill: parent
                    source: "../image/videoController/fullScreen.png"
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        if(isFullScreen)
                        {
                            isFullScreen = false


                            mainWindow.width = previousWidth
                            mainWindow.height = previousHeight

                            xflag = true
                            xRflag = true

                            mainItem.exitfullScreen()
                            rightbt.visible = true
                            leftbu.opacity = 0.5

                        }
                        else{
                            //                            console.log("全屏")
                            isFullScreen = true

                            mainWindow.width = Screen.desktopAvailableWidth
                            mainWindow.height = Screen.desktopAvailableHeight

                            xflag = false
                            xRflag = false

                            mainItem.fullScreen()
                            rightbt.visible = false
                            leftbu.opacity = 0
                        }
                    }
                }
            }

            Rectangle{
                id:star
                width: parent.height
                height: parent.height

                anchors.right: fullScreen.left
                anchors.rightMargin: 20
                //            color: "green"
                Image {
                    width: parent.height
                    height: parent.height
                    anchors.fill: parent
                    source: "../image/videoController/star.png"
                }
            }

            Rectangle{
                id:voiceController
                width: 4 * parent.height
                height: parent.height

                anchors.right: star.left
                anchors.rightMargin: 20
                //            color: "green"

                Slider{
                    id:voiceBar
                    width: parent.width
                    anchors.verticalCenter: parent.verticalCenter
                    from: 0
                    to:100
                    value: 50

                    background: Rectangle {
                        x: voiceBar.leftPadding
                        y: voiceBar.topPadding + voiceBar.availableHeight / 2 - height / 2
                        implicitWidth: 200
                        implicitHeight: 4
                        width: voiceBar.availableWidth
                        height: implicitHeight
                        radius: 2
                        color: "#bdbebf"

                        Rectangle {
                            width: voiceBar.visualPosition * parent.width
                            height: parent.height
                            color: "#00BBFF"
                            radius: 2
                        }
                    }

                    handle: Rectangle{
                        x:voiceBar.leftPadding + voiceBar.visualPosition * (voiceBar.availableWidth - width)
                        y: voiceBar.topPadding + voiceBar.availableHeight / 2 - height / 2
                        color:voiceBar.pressed ? "#00BBFF":"white";
                        border.color: "gray";
                        width: 10;
                        height: 10;
                        radius: 12;
                    }

                }

            }

            Rectangle{
                id:voice
                width: parent.height
                height: parent.height

                anchors.right: voiceController.left
                Image {
                    width: voice.height
                    height: parent.height
                    anchors.fill: parent
                    source: "../image/videoController/volumeUp.png"
                }
            }
        }
    }

    function stopPlay(){
        note.visible = false
        stopVideo = true
        firstPlay = false
        playing = false

        progressBar.value = 0
        duation.text = "00:00:00"
        timing.text = "00:00:00"

        if(!noResurce)
            player.stop(true,player.width,player.height)
        else
            player.stop(false,player.width,player.height)

        noResurce = false
    }

}
