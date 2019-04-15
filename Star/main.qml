import QtQuick 2.11
import QtQuick.Window 2.11
import "TopArea"
import "MiddleArea"

Window {
    visible: true
    id: mainWindow
    minimumHeight: 670
    minimumWidth: 1075
    title: qsTr("Star")
    TopArea{
        id: topArea
        visible: true
    }
    MiddleArea {
        id:middleArea
        visible:visible
    }
}
