
import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

Rectangle{
    id:recordPage
    width: /*59/60**/right_stack.width
    height: /*59/60**/right_stack.height
//    color: "red"

    color: "#8B8378"
    property var commentData:new Date()

    property var vect:JSON.parse(client.showCommentInfo(play.name))

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
                text: audienceInterface.audienceName//"name"
            }
            Rectangle{
                id:record_edit
                anchors.top:nametext.bottom
                width: recordPage.width
                height: 2/17*recordPage.height
                border.color: "black"
                color: "#8B8378"
                CommentPopup{
                    id:commentpop
                }

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
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            vect = JSON.parse(client.showCommentInfo(play.name))
                        }
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
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            vect = JSON.parse(client.showGoodComment(play.name))
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

//    Connections{
//        target: client
//        onInsertSuccessed: {
//            summary_stack.push(allRecord,StackView.Immediate)
////            vect = JSON.parse(client.showCommentInfo(play.name))
//        }
//    }

//    ListModel{
//        id:list
//    }

//   Component.onCompleted: {
//       var length = Object.keys(vect.resource).length
//       var c = vect.resource
//       for(var i = 0; i != length;i++){
//           list.append({name1:c[i].audienceName,message:c[i].comment,time:c[i].time})
//           console.log(c[i].audienceName+"  hdsd")
//       }
//        console.log(length+"jfjdj")
//   }

//    function addComment(an,c,t){
//        list.append({audienceName:an,comment:c,time:t})
//    }
}
