import QtQuick 2.15
import QtQuick.Controls 2.15

Switch {
    id: control
    property string optionText: "Option"
    property int identificator: 0

    signal stateChanged(int identificator, bool position)

    onClicked: stateChanged(identificator, checked)

    text: qsTr(optionText)

    indicator: Rectangle {
            implicitWidth: 50
            height: 15
            x: control.leftPadding
            y: parent.height / 2 - height / 2
            radius: 13
            color: control.checked ? "#173796" : "#ffffff"
            border.color: control.checked ? "#173796" : "#cccccc"

            Rectangle {
                x: control.checked ? parent.width - width : 0
                y: parent.height / 2 - height / 2
                width: 26
                height: 26
                radius: 13
                color: "#ffffff"
                border.color: "#cccccc"
            }
        }

        contentItem: Text {
            text: control.text
            font.pointSize: 10
            opacity: enabled ? 1.0 : 0.3
            color: "black"
            verticalAlignment: Text.AlignVCenter
            leftPadding: control.indicator.width + control.spacing
        }

}