import QtQuick 2.0
import QtQuick.Controls 2.2

Popup {
    background:  Rectangle{
        width: parent.width
        height: parent.height
        color: "#424242"
    }

    x:0
    y:0

   width: parent.width
   height: 100
   Rectangle{
       id:reply_rec
       width: parent.width
       height: parent.height-20
       color: "#8B8378"
       TextEdit{
           id:reply_edit
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
       width: 60
       height: 20
       color: "yellow"
       anchors.bottom:parent.bottom
       anchors.left: parent.left
       anchors.leftMargin: 25
       Button{
           anchors.fill: parent
           text: "关闭"
           onClicked: {
               dd.close()
           }
       }
   }

   Rectangle{
       id:re
       width: 60
       height: 20
       color: "yellow"
       anchors.bottom:parent.bottom
       anchors.right: parent.right
       Button{
           anchors.fill: parent
           text: "确认"
           onClicked: {
               dd.close()
               list.insert(0,{name:"ff",message:reply_edit.text,time:"3.1"})
           }
       }
   }
}
