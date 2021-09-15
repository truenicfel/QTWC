import QtQuick 2.15
import QtQuick.Controls 2.15

Switch {
    id: control
    property string optionText: "Option"
    property int identificator: 0

    signal stateChanged(int identificator, bool position)

    onClicked: stateChanged(identificator, checked)

    text: qsTr(optionText)

    background: Rectangle {
        color: "#e6e6e6"
    }

    indicator: Rectangle {
        implicitWidth: 35
        height: 12
        x: control.leftPadding
        y: parent.height / 2 - height / 2
        radius: 13
        color: control.checked ? "#173796" : "#ffffff"
        border.color: control.checked ? "#173796" : "#cccccc"

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
        font.pointSize: 6
        color: "black"
        verticalAlignment: Text.AlignVCenter
        leftPadding: control.indicator.width + control.spacing
    }

}