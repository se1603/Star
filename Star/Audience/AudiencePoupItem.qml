import QtQuick 2.0
import QtQuick.Controls 2.2

Popup {
    id: audienceitem

    width: 1 / 3 * mainWindow.width
    height: 1 / 2 * mainWindow.height

    x: 1 / 2 * (mainWindow.width - login.width)
    y: 1 / 5 * mainWindow.height

    focus: true
    closePolicy: Popup.CloseOnEscape

    LoginItem {
        id: login
        visible: true
    }

    RegisterItem {
        id: register
        visible: false
    }
}
