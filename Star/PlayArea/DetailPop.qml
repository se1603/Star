import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3


Popup {
    id:detailPop

    property var dataModel: JSON.parse(client.getActorInfo(play.name))

    width: 59/60*right_stack.width
    height:59/60*right_stack.height-200
    background:  Rectangle{
        width: parent.width
        height: parent.height
        color: "#424242"
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
                id:allre
                width: parent.width
                height:info.implicitHeight+rigin.implicitHeight+imagRect.implicitHeight+1000+column1.implicitHeight
                Rectangle{
                    id:imagRect
                    width: parent.width
                    height:text_name.implicitHeight
                     color: "#424242"
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
                        color: "white"
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
                    color: "#424242"
                    Text{
                        id:text_regin
                        text:play.datas.resource.region /*"China"*/
                        color: "white"

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
                    color: "#424242"
                    Row{
                        spacing: 5
                        Repeater{
                            model: play.datas.resource.videotype
                            Rectangle{
                                color: "#424242"
                                width: text_type.implicitWidth
                                height: text_type.implicitHeight
                                Text{
                                    id:text_type
                                    text: "/"+modelData.type
                                    color: "white"
                                }
                            }
                        }
                    }
                }

                Rectangle{
                    id:info
                    //                    anchors.top: grid.bottom
                    anchors.top:rec_imag.bottom
                    anchors.topMargin: 10
                    anchors.left: parent.left
                    height: infoma.implicitHeight
                    width: detailPop.width
                    color: "#424242"
                    Text{
                        id:text_in
                        anchors.left: parent.left
                        anchors.top:parent.top
                        text: "简介"
                        font.pixelSize: 24
                        color: "white"
                    }

                    Text{
                        id:infoma
                        anchors.top: text_in.bottom
                        wrapMode: Text.Wrap
                        width: mainWindow.width < 1200 ? 180 : 240
                        text:play.datas.resource.introduction
                        color: "white"
                    }
                }

                Column{
                    id:column1
                    anchors.top: info.bottom
                    anchors.topMargin: 40
                    spacing: 10
                    Repeater{
                        model: dataModel.resource
                        Rectangle{
                            width: 150
                            height: 200
                             color: "#424242"
                            Rectangle{
                                id:imge
                                width: 150
                                height: 150
                                radius: width/2
                                 color: "#424242"
                                Image{
                                    width: 150
                                    height: 150
                                    source: "file:"+modelData.post
                                }
                            }


                            Text{
                                id:namete
                                anchors.top: imge.bottom
                                anchors.topMargin: 6
                                text: modelData.name
                                color: "white"
                            }
                            Text{
                                id:type
                                anchors.top: namete.bottom
                                anchors.topMargin: 6
                                text: modelData.type
                                color: "white"
                            }
                        }
                    }
                }

            }
        }
    }
}
