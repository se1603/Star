//Author:徐丹
//time：2019.4.28
//评论界面

import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

//import QtQuick 2.12
Rectangle{
    id:recordPage
    width: 59/60*right_stack.width
    height: 59/60*right_stack.height

    color: "#8B8378"

    Rectangle{
        id:topRec
        width: recordPage.width
        height: 6/17*recordPage.height

        Column{
            id:column
            spacing: 2
            anchors.fill: parent
            Text{
                id:nametext
                anchors.top: parent.top
                font.family: "Beta Dance"
                font.pixelSize: 24
                text: "name"
            }
            Rectangle{
                id:record_edit
                anchors.top:nametext.bottom
                width: recordPage.width
                height: 2/17*recordPage.height
                border.color: "black"
                color: "#8B8378"
                TextEdit{
                    id:edit
                    width: parent.width
                    height: parent.height
                    font.family: "Helvetica"
                    font.pointSize: 20
                    color: "blue"
                    text: "please input record"
                    wrapMode: TextEdit.Wrap
                    focus: true
                }
            }
            Rectangle{
                id:record_button
                width: 120
                height: 40
                anchors.top:record_edit.bottom
                anchors.right:parent.right
                color: "#8B8378"
                Text{
                    anchors.fill: parent
                    color: "blue"
                    text: "show record"
                    font.family: "Beta Dance"
                    font.pixelSize: 24
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        add(edit.text)
                        //                        nametext.text = edit.text
                        edit.clear()
                    }
                }
            }

            Row{
                id:record_row
                anchors.top: record_button.bottom
                anchors.topMargin: 15
                spacing: 2

                Rectangle{
                    width: recordPage.width/2-1
                    height: 1/17*recordPage.height
                    color: "#8B8378"
                    Text{
                        anchors.centerIn: parent.Center
                        color: "black"
                        text: "全部评论"
                        font.family: "Beta Dance"
                        font.pixelSize: 18
                    }
                }
                Rectangle{
                    width: recordPage.width/2-1
                    height: 1/17*recordPage.height
                    color: "#8B8378"
                    Text{
                        anchors.centerIn: parent.Center
                        color: "black"
                        text: "精华评论"
                        font.family: "Beta Dance"
                        font.pixelSize: 18
                    }
                }
            }
        }
    }
    Rectangle{
        id:summary_rec
        anchors.top:topRec.bottom
        anchors.left: parent.left
        width: recordPage.width
        height: 11/17*recordPage.height
        border.color: "grey"

        StackView{
            width: parent.width
            height: parent.height
            id:summary_stack
            anchors.fill: parent
            initialItem: allRecord
        }
        Component{
            id:allRecord
            AllComment{
                model: list
            }
        }
    }

    ListModel{
        id:list
    }

    function add(text){
        list.append({name:"ff",message:text,time:"3.1"})
    }

}
