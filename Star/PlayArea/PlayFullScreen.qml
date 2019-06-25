import QtQuick 2.0
import QtQuick.Window 2.12
import QtQuick.Controls 2.0

Window {
    id:fullScreen
    width: Screen.desktopAvailableWidth
    height: Screen.desktopAvailableHeight

    property alias fullWindow: videoWindow

   PlayVideo{
       id:videoWindow

   }
}
