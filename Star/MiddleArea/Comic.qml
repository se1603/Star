//time：2019.4.15
//内容：动漫
import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Item {
    id:comic
    width: page_display.width
    height: page_display.height

   property var comics
    StackView{
        id: comic_stack
        anchors {
            fill: parent
        }
        initialItem: comicRecommend_page
    }
    Component{
        id:comicRecommend_page
        ComicRecommend{

        }
    }
    Component{
        id:comictype_page
        ComicType{

        }
    }

}
