import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import "../MiddleArea"

Rectangle {
    width: 59 / 60 * audienceDisplay.width
    height: 59 / 60 * audienceDisplay.height
    border.color: "gray"

    property var mycollection:["全职高手01","头文字D","诺丁山","真爱至上","了不起的麦瑟尔夫人第二季03","百年酒馆09","秘密花园06","1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","10","11","12","13","14","15","16"]

    ScrollView {
        anchors.fill: parent
        clip: true
        ColumnLayout {
            width: parent.width
            height: parent.height

            Text {
                id: collection_title
                text: "   My Collection Video"
                font.pixelSize: 20
                font.family: "Beta Dance"
                opacity: 0.7
            }
            GridLayout {
                id: collection_grid
                anchors.top: collection_title.bottom
                anchors.topMargin: 15
                anchors.left: parent.left
                anchors.leftMargin: 15
                columns: 5
                columnSpacing: 15
                rowSpacing: 15
                Repeater {
                    model: mycollection
                    AudienceVideoRec {
                    }
                }
            }
        }
    }
}
