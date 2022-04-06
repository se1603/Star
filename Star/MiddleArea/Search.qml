import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import "../TopArea"

Item {
    id:search111
    width: page_display.width
    height: page_display.height
    property alias search: search_stack



    StackView{
        id: search_stack
        anchors {
            fill: parent
        }
        initialItem: searchcharacter

    }
    Component{
        id:searchmovie
        SearchMovie{
        }
    }
    Component{
        id:searchdrama
        SearchDrama{

        }
    }
    Component{
        id:searchcharacter
        SearchCharacter{

        }
    }
    Component{
        id:searchnone
        SearchNone{

        }
    }

    function searchPage(page){
        switch(page){
        case "Film":
            search_stack.push(searchmovie, StackView.Immediate)
            break;
        case "Drama":
            search_stack.push(searchdrama, StackView.Immediate)
            break;
        case "Comic":
            search_stack.push(searchdrama, StackView.Immediate)
            break;
        case "None":
            search_stack.push(searchnone, StackView.Immediate)
            break;
        default:
            search_stack.push(searchcharacter, StackView.Immediate)
            break;
        }
    }

}
