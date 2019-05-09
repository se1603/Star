import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Rectangle {
    id:movie
    width: page_display.width
    height: page_display.height

    property var films

    StackView {
        id: film_stack
        anchors {
            fill: parent
        }
        initialItem:recommend_film
    }

    Component{
        id:recommend_film
        MovieRecommend{

        }
    }

    Component{
        id:common_film
        MovieType{

        }
    }
}
