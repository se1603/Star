
import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

Rectangle{
    id:recordPage
    width: /*59/60**/right_stack.width
    height: /*59/60**/right_stack.height
    //    color: "red"

    color: "#424242"
    property var commentData:new Date()

    property var vect:JSON.parse(client.showCommentInfo(play.name))

    Rectangle{
        id:topRec
        width: recordPage.width
        height: 6/17*recordPage.height

        color: "#424242"
        Column{
            id:column
            spacing: 2
            anchors.fill: parent
            Text{
                id:nametext
                anchors.top: parent.top
                font.pixelSize: 18
                text: audienceInterface.audienceName//"name"
                color: "#A9A9A9"
                MouseArea{
                    anchors.fill: parent
                    hoverEnabled: true
                    enabled: true
                    onEntered: {
                        parent.color = "red"
                    }
                    onExited: {
                        parent.color = "blue"
                    }
                }
            }
            Rectangle{
                id:record_edit
                anchors.top:nametext.bottom
                width: recordPage.width
                height: 2/17*recordPage.height

                color: "#8B8378"
                CommentPopup{
                    id:commentpop
                }

                TextEdit{
                    id:edit
                    width: parent.width
                    height: parent.height
                    font.pointSize: 16
                    color: "#F5F5F5"
                    wrapMode: TextEdit.Wrap
                    focus: true
                }
            }
            Rectangle{
                id:record_button
                width: 90
                height: 1/19*recordPage.height//40
                anchors.top:record_edit.bottom
                anchors.topMargin: 5
                anchors.right:parent.right
                color: "#1E90FF"
                Text{
//                    anchors.fill: parent
                    anchors.centerIn: parent
                    color: "white"
                    text: "发表评论"
                    font.pixelSize: 16
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        var year = commentData.getFullYear()
                        var month = commentData.getMonth()+1
                        var day = commentData.getDate()
                        var hours = commentData.getHours()
                        var minutes = commentData.getMinutes()
                        var commenttime = year+"-"+month+"-"+day+"-"+hours+":"+minutes
                        if(nametext.text == ""){
                            commentpop.open()
                        }else{
                            //addComment(nametext.text,edit.text,commenttime)
                            client.addComment(nametext.text,play.name,commenttime,edit.text)
                            vect = JSON.parse(client.showCommentInfo(play.name))
                            edit.clear()
                        }
                    }
                }
            }

            Row{
                id:record_row
                anchors.top: record_button.bottom
                anchors.topMargin: 15
                spacing: 2

                Rectangle{
                    id:allcom
                    width: recordPage.width/2-1
                    height: 1/19*recordPage.height
                    color: "#1E90FF"

                    Text{
                        anchors.centerIn: parent
                        color: "white"
                        text: "全部评论"
                        font.pixelSize: 14
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            vect = JSON.parse(client.showCommentInfo(play.name))

                            allcom.color = "#1E90FF"
                            selectcom.color = "#8B8378"

                        }
                    }
                }
                Rectangle{
                    id:selectcom
                    width: recordPage.width/2-1
                    height: 1/19*recordPage.height
                    color: "#8B8378"

                    Text{
                        anchors.centerIn: parent
                        color: "white"
                        text: "精华评论"

                        font.pixelSize: 14
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            vect = JSON.parse(client.showGoodComment(play.name))

                            allcom.color = "#8B8378"
                            selectcom.color = "#1E90FF"

                        }
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
                models:vect.resource
            }
        }
    }

}
