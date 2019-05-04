import QtQuick 2.0
import QtQuick.Controls 2.2

Rectangle {
    width: 59 / 60 * parent.width
    height: 59 / 60 * parent.height
    anchors.centerIn: parent

    property string audienceName:""

    Row {
        width: parent.width
        height: parent.height
        spacing: 1 / 60 * parent.width

        AudienceMenu {
            id: audienceMenu
        }

        Rectangle {
            id: audienceDisplay
            width: 51 / 60 * parent.width
            height: parent.height

            StackView {
                id: audience_stack
                anchors {
                    fill: parent
                }
                initialItem:collection_page
            }

            Component {
                id: collection_page
                AudienceCollection {
                }
            }

            Component {
                id: record_page
                AudienceRecord {
                }
            }

            Component {
                id: message_page
                AudienceMessage {
                }
            }
        }
    }
}
