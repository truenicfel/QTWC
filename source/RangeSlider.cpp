#include "QTWC/RangeSlider.h"

#include <QQuickItem>
#include <QQmlProperty>

#include <stdexcept>

#include "QMLPaths.h"

namespace QTWC {

	RangeSlider::RangeSlider(double rangeBegin, double rangeEnd, const std::string& title, Qt::Orientation orientation) {

        setResizeMode(QQuickWidget::SizeRootObjectToView);
        if (orientation == Qt::Orientation::Horizontal) {
            setSource(QUrl::fromLocalFile(RANGE_SLIDER_HORIZONTAL_QML));
            setMinimumHeight(50);
        } else {
            setSource(QUrl::fromLocalFile(RANGE_SLIDER_VERTICAL_QML));
            setMinimumWidth(30);
        }

        // set the title
        QQmlProperty::write(rootObject(), "titleText", title.c_str());

        QQmlProperty::write(rootObject(), "fromValue", rangeBegin);
        QQmlProperty::write(rootObject(), "toValue", rangeEnd);

        // extract a list of items below the slider
        auto* slider = rootObject()->findChild<QQuickItem *>("slider");
        const QList<QQuickItem *>& list = slider->childItems();

        // there is 3 children that I added and there is 2 more
        // from the original rangeslider implementation
        // the last one from the original implementation is the bar that
        // the handles "slide" on
        // change the color of that
        list.at(5)->setProperty("color", "#999a9e");

        // the bar has a single child that shows the current range
        // change the color of that
        const QList<QQuickItem *>& listOfBar = list.at(5)->childItems();
        listOfBar.at(0)->setProperty("color", "#173796");

        bool success = QObject::connect(rootObject(), SIGNAL(firstMoved(double)), this, SLOT(leftMoved(double)));
        if (!success) {
            throw std::runtime_error("The connection between slider value changes and slot did not work!");
        }
        success = QObject::connect(rootObject(), SIGNAL(secondMoved(double)), this, SLOT(rightMoved(double)));
        if (!success) {
            throw std::runtime_error("The connection between slider value changes and slot did not work!");
        }

	}

	void RangeSlider::leftMoved(double value) {
        double rightValue = QQmlProperty::read(rootObject(), "secondValue").toDouble();
        emit rangeChanged(value, rightValue);
	}

    void RangeSlider::rightMoved(double value) {
        double leftValue = QQmlProperty::read(rootObject(), "firstValue").toDouble();
        emit rangeChanged(leftValue, value);
    }
}