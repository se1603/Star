import QtQuick 2.11
import QtQuick.Window 2.11
import "TopArea"
import "MiddleArea"
import "Audience"
import Star 1.0

Window {
    visible: true
    id: mainWindow
    minimumHeight: 670
    minimumWidth: 1075
    title: qsTr("Star")
    property string name:mainItem.middleArea.audienceInterface.audienceName

    Client {
        id: client
    }

    MainItem {
        id: mainItem
    }

    Connections{
        target: mainWindow
        onClosing: {
            if(name !== ""){
                client.loginOut(name)
            }
        }
    }
}
