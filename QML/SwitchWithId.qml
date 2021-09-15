import QtQuick 2.15
import QtQuick.Controls 2.15

Switch {
    id: control
    property string optionText: "Option"
    property int identificator: 0
    property double fontSize: 8
    property string backgroundColor: "#e6e6e6"

    signal stateChanged(int identificator, bool position)

    onClicked: stateChanged(identificator, checked)

    text: qsTr(optionText)

    background: Rectangle {
        color: backgroundColor
    }

    indicator: Rectangle {
        implicitWidth: 35
        height: 12
        x: control.leftPadding
        y: parent.height / 2 - height / 2
        radius: 13
        color: control.checked ? "#173796" : "#ffffff"
        border.color: control.checked ? "#173796" : "#cccccc"

        anchors.left: control.left
        anchors.verticalCenter: control.verticalCenter
        anchors.leftMargin: 3

        Rectangle {
            x: control.checked ? parent.width - width : 0
            y: parent.height / 2 - height / 2
            width: 20
            height: 20
            radius: 10
            color: "#ffffff"
            border.color: "#cccccc"
        }
    }

    contentItem: Text {
        text: control.text
        font.pointSize: fontSize
        color: "black"
        anchors.left: control.indicator.right
        anchors.verticalCenter: control.verticalCenter
        anchors.leftMargin: 3
    }

}