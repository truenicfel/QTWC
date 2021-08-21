import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Styles 1.4

Rectangle {
    id: rangeSliderRoot
    color: "white"
    property alias firstValue: slider.first.value
    property alias secondValue: slider.second.value
    property alias fromValue: slider.from
    property alias toValue: slider.to
    property string titleText: "Title"
    property int labelPrecision: 4
    height: 50

    signal firstMoved(double value)
    signal secondMoved(double value)

    RangeSlider {
        id: slider
        from: 0
        to: 1
        first.value: 0.0
        second.value: 1.0
        orientation: Qt.Horizontal
        width: parent.width - ((labelPrecision + 1) * 13)
        anchors.horizontalCenter: rangeSliderRoot.horizontalCenter
        anchors.verticalCenter: rangeSliderRoot.verticalCenter
        first.handle.width: 10
        second.handle.width: 10
        objectName: "slider"

        first.onMoved: rangeSliderRoot.firstMoved(first.value)
        second.onMoved: rangeSliderRoot.secondMoved(second.value)

        Text {
            id: firstHandleText
            text: round(slider.first.value)
            anchors.top: slider.first.handle.verticalCenter
            anchors.topMargin: 5
            anchors.right: slider.first.handle.left
            anchors.rightMargin: 3
            font.pointSize: 8;
        }

        Text {
            id: secondHandleText
            text: round(slider.second.value)
            anchors.top: slider.second.handle.verticalCenter
            anchors.topMargin: 5
            anchors.left: slider.second.handle.right
            anchors.leftMargin: 2
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