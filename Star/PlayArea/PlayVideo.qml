/*
  Author:王梦娟
  Date:2019-5-25
*/
import QtQuick 2.0
import Star 1.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls 2.5

Rectangle {
    width: parent.width
    height: parent.height

    property string path: ""
    property bool pause: false
    property bool playing: false

    Rectangle{
        id: playVideo
        width: parent.width
        height: parent.height
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
                console.log(path)
                playing = true
                player.startPlay(path)
                //                console.log(allController.height)
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
    }

    Connections{
        target: player
        onSigShowCurrentTime:
        {
            //            console.log(player.showCurrentTime())
            timing.text = player.showCurrentTime()
        }
    }

    Connections{
        target: player
        onSigSliderTotalValue:{
            progressBar.to = value
            console.log(progressBar.to)
        }
        onSigSliderValue:{
            progressBar.value = currentvalue
//            console.log(progressBar.value)
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
                    source: playing ? "../image/videoController/pause.png" : "../image/videoController/play.png"
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {

                        if(pause)
                        {
                            player.play()
                            pause = false
                            playing = true
                        }
                        else if(playing)
                        {
                            player.pause()
                            playing = false
                            pause = true
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
                        player.stop()
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

}
