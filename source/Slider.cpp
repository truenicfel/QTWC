#include "QTWC/Slider.h"

#include <QQuickItem>
#include <QQmlProperty>

#include "QMLPaths.h"

namespace QTWC {

	Slider::Slider(double rangeBegin, double rangeEnd, const std::string& title)
    : mRangeBegin(rangeBegin)
    , mRangeEnd(rangeEnd)
    {

        setResizeMode(QQuickWidget::SizeRootObjectToView);
        setSource(QUrl::fromLocalFile(SLIDER_HORIZONTAL_QML));
        setMinimumHeight(50);


        // set the title
        QQmlProperty::write(rootObject(), "titleText", title.c_str());

        QQmlProperty::write(rootObject(), "fromValue", rangeBegin);
        QQmlProperty::write(rootObject(), "toValue", rangeEnd);

        // extract a list of items below the slider
        auto* slider = rootObject()->findChild<QQuickItem *>("slider");
        const QList<QQuickItem *>& list = slider->childItems();

        // there is 2 children that I added and there is 2 more
        // from the original rangeslider implementation
        // the last one from the original implementation is the bar that
        // the handles "slide" on
        // change the color of that
        list.at(3)->setProperty("color", "#999a9e");

        // the bar has a single child that shows the current range
        // change the color of that
        const QList<QQuickItem *>& listOfBar = list.at(3)->childItems();
        listOfBar.at(0)->setProperty("color", "#173796");

        bool success = QObject::connect(rootObject(), SIGNAL(moved(double)), this, SLOT(receiveMoved(double)));
        if (!success) {
            throw std::runtime_error("The connection between slider value changes and slot did not work!");
        }

	}

    void Slider::receiveMoved(const double& value) {
        emit sliderValueChanged(value);
    }

    void Slider::setSliderValue(double value) {
        if (value < mRangeBegin) {
            QQmlProperty::write(rootObject(), "value", mRangeBegin);
        } else if (value > mRangeEnd) {
            QQmlProperty::write(rootObject(), "value", mRangeEnd);
        } else {
            QQmlProperty::write(rootObject(), "value", value);
        }
    }
}