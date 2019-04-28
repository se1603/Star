import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Rectangle {
    id:selectPage

    width: /*59 / 60 **/page_display.width
    height: 59 / 60 *page_display.height

    ScrollView {
        anchors.fill: parent
        clip: true
        ColumnLayout {
            width: parent.width
            height: parent.height

            Slide{
                id:slide
                anchors.top:parent.top
            }

            Column{
                anchors.top:slide.bottom
                anchors.topMargin: 20
                spacing: 10
                Repeater{
                    model: selectModel2
                    Rectangle {
                        id:item
                        width:selectPage.width
                        height:370
                        Text { id: nameField; text: name }

                        GridLayout{
                            id:grid
                            columns:4
                            width: parent.width
                            anchors.top:nameField.bottom
                            //                columnSpacing: 10
                            rowSpacing: 20
                            Repeater {
                                model: attributes
                                Rectangle{
                                    width: 1/5 * item.width + 10
                                    height: 150
                                    color: "#dd22dd"
                                    Text{
                                        anchors.top: parent.bottom
                                        text: url
                                    }

                                }
                            }
                        }
                    }
                }
            }
        }
    }

    ListModel {
        id: selectModel2

        ListElement{
            name:"动漫精选"
            attributes:[
                ListElement{
                    url:"动漫精选1"
                },
                ListElement{
                    url:"动漫精选2"
                },
                ListElement{
                    url:"动漫精选3"
                },
                ListElement{
                    url:"动漫精选4"
                },
                ListElement{
                    url:"动漫精选5"
                }
            ]
        }

        ListElement{
            name:"电影精选"
            attributes:[
                ListElement{
                    url:"电影精选1"
                },
                ListElement{
                    url:"电影精选2"
                },
                ListElement{
                    url:"电影精选3"
                },
                ListElement{
                    url:"电影精选4"
                },
                ListElement{
                    url:"电影精选5"
                }
            ]
        }
        ListElement{
            name:"剧集精选"
            attributes:[
                ListElement{
                    url:"剧集精选1"
                },
                ListElement{
                    url:"剧集精选2"
                },
                ListElement{
                    url:"剧集精选3"
                },
                ListElement{
                    url:"剧集精选4"
                },
                ListElement{
                    url:"剧集精选5"
                }
            ]
        }
    }

    //    Component {
    //        id: selectDelegate1
    //        Rectangle {
    //            id:item
    //            width:selectPage.width
    //            height:370
    //            Text { id: nameField; text: name }

    //            GridLayout{
    //                id:grid
    //                columns:4
    //                width: parent.width
    //                anchors.top:nameField.bottom
    //                //                columnSpacing: 10
    //                rowSpacing: 20
    //                Repeater {
    //                    model: attributes
    //                    Rectangle{
    //                        width: 1/5 * item.width + 10
    //                        height: 150
    //                        color: "#dd22dd"
    //                        Text{
    //                            anchors.top: parent.bottom
    //                            text: url
    //                        }

    //                    }
    //                }
    //            }
    //        }
    //    }

}
