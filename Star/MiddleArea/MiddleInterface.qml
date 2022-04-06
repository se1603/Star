import QtQuick 2.0
import QtQuick.Controls 2.5

Rectangle {
    width: 59 / 60 * middleArea.width
    height: 59 / 60 * middleArea.height
    anchors.centerIn: middleArea

    property var searchMovie
    property var searchDrama
    property var searchCharacter
    property var searchNone

    property alias middlemenu: middle_Menu

    property alias showPage: page_display

    property alias search: searchfunction

    property alias middleStack:middle_stack
    property alias recordPage:browserecord_page

    property var browse_records


    Row {
        width: parent.width
        height: parent.height
        spacing: 1 / 60 * parent.width

        MiddleMenu {
            id: middle_Menu
            visible: true
        }
        Search{
            id: searchfunction
            visible: false
        }


        Rectangle {
            id: page_display
            width: 54 / 60 * parent.width
            height: parent.height

//            color: "red"

            StackView {
                id: middle_stack
                anchors {
                    fill: parent
                }
                initialItem:select_page
            }

            Component {
                id: select_page

                SelectPage {
                }
            }

            Component{
                id:drama_page
                Drama{

                }
            }
            Component{
                id:movie_page
                Movie{

                }
            }
            Component{
                id:variety_page
                Variety{

                }
            }
            Component{
                id:comic_page
                Comic{

                }
            }

            Component{
                id:search_page
                Search{
                }
            }

            Component{
                id:browserecord_page
                BrowseRecord{

                }
            }
        }
    }
}
