import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Styles 1.4

Rectangle {
    id: sliderRoot
    color: "#e6e6e6"
    property alias value: slider.value
    property alias fromValue: slider.from
    property alias toValue: slider.to
    property string titleText: "Title"
    property int labelPrecision: 4
    height: 50

    signal moved(double value)

    Slider {
        id: slider
        from: 0
        to: 1
        value: 0.0
        orientation: Qt.Horizontal
        width: parent.width - ((labelPrecision + 1) * 13)
        anchors.horizontalCenter: sliderRoot.horizontalCenter
        anchors.verticalCenter: sliderRoot.verticalCenter
        handle.width: 10
        objectName: "slider"

        onMoved: sliderRoot.moved(value)

        Text {
            id: handleText
            text: round(slider.value)
            anchors.top: slider.handle.verticalCenter
            anchors.topMargin: 5
            anchors.right: slider.handle.left
            anchors.rightMargin: 3
            font.pointSize: 8;
        }

        Text {
            text: titleText
            anchors.horizontalCenter: slider.horizontalCenter
            anchors.verticalCenter: slider.verticalCenter
            anchors.verticalCenterOffset: -20
            font.pointSize: 10; font.bold: true
        }

    }

    function round(number) {
        return number.toPrecision(labelPrecision)
    }

}