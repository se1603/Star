import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Rectangle {
    width: page_display.width
    height: page_display.height
//    color: "yellow"
    property var films

    ScrollView {
            anchors.fill: parent
            clip: true
            ColumnLayout {
                width: parent.width
                height: parent.height

                Row{
                    id: row_menu
                    anchors.left:parent.left
                    spacing: 50
                    Repeater {
                        model:JSON.parse(client.showCategory(1))
                        delegate: categoryDelegate
                    }
                }

                GridLayout {
                    id: film_grid
                    anchors.top: collection_title.bottom
                    anchors.topMargin: 15
                    anchors.left: parent.left
                    anchors.leftMargin: 15
                    columns: page_display.width < 1000 ? 4 : 5
                    columnSpacing: page_display.width < 1000 ? 15 : 20
                    rowSpacing: 15
                    Repeater {
                        model: films
                        Rectangle {
                            id:image
                            width: 220
                            height: 330
//                            border.color: "red"
                            Image {
                                anchors.fill: parent
                                anchors.top: parent.top
                                source:"file:" + modelData.post
                            }
                            Rectangle {
                                id: filmname
                                width: parent.width
                                height: 30
                                anchors.bottom: parent.bottom
//                                border.color : "green"
                            }
                            Text {
                                id: collection_text
                                width: parent.width
                                text: modelData.name
                                font.pixelSize: 15
                                wrapMode: Text.Wrap
                                anchors.top: filmname.top
                            }

                            MouseArea{
                                anchors.fill: parent
                                onClicked: {
                                    console.log(modelData.name)
                                }
                            }
                        }
                    }
                }
            }
        }

    Component{
        id:categoryDelegate
        Rectangle {
            width: 50
            height : 40
            Text {
                id:category
                text: modelData.category
                opacity: 0.5
                font.pixelSize: 15
                color: 	"#808080"
                anchors.horizontalCenter: parent.horizontalCenter
                MouseArea {
                    anchors.fill: parent
                    acceptedButtons: Qt.RightButton | Qt.LeftButton
                    hoverEnabled: true
                    enabled: true

                    onEntered: {
                        parent.color = "#00BFFF"
                    }
                    onExited: {
                        parent.color = "#808080"
                    }
                    onClicked: {
                        if(category.text === "动画")
                            films = JSON.parse(client.browseFilm(1,6))
                    }
                }
            }
        }
    }
}
