import QtQuick 2.0
import QtQuick.Controls 2.2

Rectangle {
    id: variety
    width: page_display.width
    height: page_display.height

    property var varieties

    StackView {
        id: variety_stack
        anchors {
            fill: parent
        }
        initialItem: recommend_variety
    }

    Component {
        id: recommend_variety
        VarietyRecommend {

        }
    }

    Component {
        id: common_variety
        VarietyType {

        }
    }
}
