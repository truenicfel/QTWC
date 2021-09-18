import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Styles 1.4

Rectangle {
    id: rangeSliderRoot
    color: "#e6e6e6"
    property alias firstValue: slider.first.value
    property alias secondValue: slider.second.value
    property alias fromValue: slider.from
    property alias toValue: slider.to
    property int labelPrecision: 4
    property string titleText: "Title"

    signal firstMoved(double value)
    signal secondMoved(double value)

    RangeSlider {
        id: slider
        from: 0
        to: 1
        first.value: 0.0
        second.value: 1.0
        orientation: Qt.Vertical
        width: 20 + (labelPrecision + 1) * 5
        height: parent.height - 15
        anchors.horizontalCenter: rangeSliderRoot.horizontalCenter
        anchors.verticalCenter: rangeSliderRoot.verticalCenter
        first.handle.height: 10
        second.handle.height: 10
        objectName: "slider"

        first.onMoved: rangeSliderRoot.firstMoved(first.value)
        second.onMoved: rangeSliderRoot.secondMoved(second.value)

        Text {
            id: firstHandleText
            text: round(slider.first.value)
            anchors.top: slider.first.handle.verticalCenter
            anchors.topMargin: 5
            anchors.left: slider.first.handle.horizontalCenter
            anchors.leftMargin: 5
            font.pointSize: 8;
        }

        Text {
            id: secondHandleText
            text: round(slider.second.value)
            anchors.bottom: slider.second.handle.verticalCenter
            anchors.bottomMargin: 5
            anchors.left: slider.second.handle.horizontalCenter
            anchors.leftMargin: 5
            font.pointSize: 8;
        }

        Text {
            text: titleText
            anchors.horizontalCenter: slider.horizontalCenter
            anchors.verticalCenter: slider.verticalCenter
            anchors.horizontalCenterOffset: -20
            font.pointSize: 10; font.bold: true
            rotation : 270
        }

    }

    function round(number) {
        return number.toPrecision(labelPrecision)
    }

}