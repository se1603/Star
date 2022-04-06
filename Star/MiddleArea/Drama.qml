import QtQuick 2.0
import QtQuick.Controls 2.2

Rectangle {
    id: drame
    width: page_display.width
    height: page_display.height

    property var drames

    StackView {
        id: drame_stack
        anchors {
            fill: parent
        }
        initialItem: recommend_drame
    }

    Component {
        id: recommend_drame
        DrameRecommend {

        }
    }

    Component {
        id: common_drame
        DrameType {

        }
    }
}
