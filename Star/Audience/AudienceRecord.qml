import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2

Rectangle {
    width: 59 / 60 * audienceDisplay.width
    height: 59 / 60 * audienceDisplay.height
    border.color: "gray"

    property var myrecord:["猫和老鼠欢乐斗地主","爱的魔力转圈圈","密室大逃脱plus","1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","10","11","12","13","14","15","16"]

    ScrollView {
        anchors.fill: parent
        clip: true
        ColumnLayout {
            width: parent.width
            height: parent.height

            Text {
                id: record_title
                text: "   My Browse Record"
                font.pixelSize: 20
                font.family: "Beta Dance"
                opacity: 0.7
            }
            GridLayout {
                id: record_grid
                anchors.top: record_title.bottom
                anchors.topMargin: 15
                anchors.left: parent.left
                anchors.leftMargin: 15
                columns: 5
                columnSpacing: 15
                rowSpacing: 15
                Repeater {
                    model: myrecord
                    AudienceVideoRec {
                    }
                }
            }
        }
    }
}
