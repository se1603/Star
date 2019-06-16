/*author:guchangrong
 *data:2019-05-21
 *调用界面显示搜索结果
 */
import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import "../TopArea"

Item {
    id:search111
    width: page_display.width
    height: page_display.height
//    property alias search: searchmovie


    StackView{
        id: search_stack
        anchors {
            fill: parent
        }
        initialItem: searchmovie
    }
    Component{
        id:searchmovie
        SearchMovie{
            id:search
        }
    }

}
