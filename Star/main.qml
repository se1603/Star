import QtQuick 2.11
import QtQuick.Window 2.11
import "TopArea"
import "MiddleArea"
import "Audience"
import Star 1.0

Window {
    visible: true
    id: mainWindow
    color: "#F5F5F5"
    minimumHeight: 670
    minimumWidth: 1075
    title: qsTr("Star")

    Client{
        id:client
    }


    MainItem {
        id: mainItem
    }

    Connections{
        target: mainWindow
        onClosing: {
            if(mainItem.middleArea.audienceInterface.audienceName !== ""){
                client.loginOut(mainItem.middleArea.audienceInterface.audienceName)
            }
        }
    }

}
