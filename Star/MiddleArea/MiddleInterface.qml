//time：2019.4.30
//内容：页面跳转组件
//author：徐丹

import QtQuick 2.0
import QtQuick.Controls 2.2

Rectangle {
    width: 59 / 60 * parent.width
    height: 59 / 60 * parent.height
    anchors.centerIn: parent

    Row {
        width: parent.width
        height: parent.height
        spacing: 1 / 60 * parent.width

        MiddleMenu {
            id: middle_Menu
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
        }
    }
}
