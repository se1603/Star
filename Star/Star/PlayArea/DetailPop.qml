import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3


Popup {
    id:detailPop

    //    width: 59/60*right_stack.width-500
    //    height: 59/60*right_stack.height

    width: 59/60*right_stack.width
    height:59/60*right_stack.height-200
    background:  Rectangle{
        width: parent.width
        height: parent.height
        color: "#8B8378"
    }

    x:0
    y:200

    ScrollView{
        anchors.fill: parent
        clip: true
        ColumnLayout{
            id:column
            width: parent.width
            height: parent.height
            Rectangle{
                width: parent.width
                height:info.implicitHeight+rigin.implicitHeight+imagRect.implicitHeight+500
//                height: 1000

                Rectangle{
                    id:imagRect
                    width: parent.width
                    height:text_name.implicitHeight
    //                color: "#8B8378"
                    Text{
                        id:text_name
                        anchors.top:parent.top
                        anchors.topMargin: 10
                        anchors.left: parent.left
                        anchors.leftMargin: 5
                        wrapMode: Text.Wrap
                        width: mainWindow.width < 1200 ? 180 : 240
                        font.pixelSize: 18
                        text:play.name//"Name"
                    }
                }
    //            Row{
    //                spacing: 5
                    Rectangle{
                        id:rigin
                        width: text_regin.implicitWidth
                        height: text_regin.implicitHeight
                        anchors.top: imagRect.bottom
                        anchors.topMargin: 10
                        anchors.left: parent.left
                        anchors.leftMargin: 5
                        color: "#8B8378"
                        Text{
                            id:text_regin
                            text: "China"
                        }
                    }
                    Rectangle{
                        id:rec_imag
                        width: 150
                        height: 15//text_type.implicitHeight
                        anchors.top:imagRect.bottom
                        anchors.topMargin: 10
                        anchors.left: rigin.right
                        anchors.leftMargin:4
                        color: "#8B8378"
                        Row{
                            spacing: 5
                            Repeater{
                                model: play.datas.resource.videotype
                                Rectangle{
                                    color: "#8B8378"
                                    width: text_type.implicitWidth
                                    height: text_type.implicitHeight
                                    Text{
                                        id:text_type
                                        text: "/"+modelData.type
                                    }
                                }
                            }
                        }
                    }
    //            }
                Rectangle{
                    id:info
                    anchors.top:rec_imag.bottom
                    anchors.topMargin: 10
                    anchors.left: parent.left
                    height: infoma.implicitHeight
                    width: detailPop.width
                    color: "#8B8378"
                    Text{
                        id:text_in
                        anchors.left: parent.left
                        anchors.top:parent.top
                        text: "简介"
                        font.pixelSize: 24
                    }

                    Text{
                        id:infoma
                        anchors.top: text_in.bottom
                        wrapMode: Text.Wrap
                        width: mainWindow.width < 1200 ? 180 : 240
                        text:play.datas.resource.introduction//"hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh"
                    }
                }
            }


        }
    }

    //    Rectangle{
    //        id:imagRect
    //        width: parent.width
    //        height:25
    //        color: "#8B8378"

    //        Text{
    //            id:text_name
    //            anchors.top:parent.top
    //            anchors.topMargin: 10
    //            anchors.left: parent.left
    //            anchors.leftMargin: 5
    //            font.pixelSize: 24
    //            font.family: "宋体"
    //            color: "black"
    //            text:play.name//"Name"
    //        }
    //    }

    //    Rectangle{
    //        id:rigin
    //        width: text_regin.implicitWidth
    //        height: text_regin.implicitHeight
    //        anchors.top: imagRect.bottom
    //        anchors.topMargin: 10
    //        anchors.left: parent.left
    //        anchors.leftMargin: 5
    //        color: "#8B8378"
    //        Text{
    //            id:text_regin
    //            text: "China"
    //        }
    //    }

    //    Rectangle{
    //        id:rec_imag
    //        width: 150
    //        height: 15//text_type.implicitHeight
    //        anchors.top:imagRect.bottom
    //        anchors.topMargin: 10
    //        anchors.left: rigin.right
    //        anchors.leftMargin:4
    //        color: "#8B8378"
    //        Row{
    //            spacing: 5
    //        Repeater{
    //            model: play.datas.resource.videotype

    //                Rectangle{
    //                    color: "#8B8378"
    //                    width: text_type.implicitWidth
    //                    height: text_type.implicitHeight
    //                    Text{
    //                        id:text_type
    //                        text: "/"+modelData.type
    //                    }
    //                }
    //            }
    //        }
    //    }

    //    Rectangle{
    //        id:info
    //        anchors.top:rec_imag.bottom
    //        anchors.topMargin: 10
    //        anchors.left: parent.left
    //        height: infoma.implicitHeight
    //        width: detailPop.width
    //        color: "#8B8378"
    //        Text{
    //            id:text_in
    //            anchors.left: parent.left
    //            anchors.top:parent.top
    //            text: "简介"
    //            font.pixelSize: 24
    //        }

    //        Text{
    //            id:infoma
    //            anchors.top: text_in.bottom
    //            wrapMode: Text.Wrap
    //            width: mainWindow.width < 1200 ? 180 : 240
    //            text:play.datas.resource.introduction//"hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh"
    //        }
    //    }

    //    Rectangle{
    //        width: 60
    //        height: 20
    //        color: "yellow"
    //        anchors.bottom:parent.bottom
    //        anchors.left: parent.left
    //        anchors.leftMargin: 25
    //        Button{
    //            anchors.fill: parent
    //            text: "关闭"
    //            onClicked: {
    //                pop.close()
    //            }
    //        }
    //    }
}
