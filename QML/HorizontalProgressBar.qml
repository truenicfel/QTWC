import QtQuick 2.12
import QtQuick.Controls 2.12

Rectangle {
    id: progressBarRoot

    property double currentProgress: 0.0
    property string titleText: "DefaultTitle"

    color: "#e6e6e6"

    ProgressBar {
        id: control
        value: currentProgress
        padding: 2

        anchors.horizontalCenter: progressBarRoot.horizontalCenter
        anchors.verticalCenter: progressBarRoot.verticalCenter

        Text {
            text: titleText
            anchors.horizontalCenter: control.horizontalCenter
            anchors.verticalCenter: control.verticalCenter
            anchors.verticalCenterOffset: -25
            font.pointSize: 12; font.bold: true
        }

        Text {
            text: round(currentProgress) + "%"
            anchors.horizontalCenter: control.horizontalCenter
            anchors.verticalCenter: control.verticalCenter
            anchors.verticalCenterOffset: 20
            font.pointSize: 10
        }

        background: Rectangle {
            implicitWidth: progressBarRoot.width - 10
            implicitHeight: 10
            color: "#757471"
            radius: 5
        }

        contentItem: Item {
            implicitWidth: progressBarRoot.width - 10
            implicitHeight: 8

            Rectangle {
                width: control.visualPosition * parent.width
                height: parent.height
                radius: 4
                color: "#173796"
            }
        }
    }

    function round(number) {
        return number.toPrecision(2)
    }

}