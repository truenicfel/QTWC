#include "QTWC/ProgressBar.h"

#include <algorithm>

#include <QQmlProperty>
#include <QQuickItem>

#include "QMLPaths.h"

namespace QTWC {

    ProgressBar::ProgressBar(const double& start, const double& end, const std::string& title)
    : mStart(start)
    , mEnd(end)
    , mProgress(start)
    {

        setResizeMode(QQuickWidget::SizeRootObjectToView);
        setSource(QUrl::fromLocalFile(HORIZONTAL_PROGRESS_BAR_QML));
        setMinimumHeight(65);

        // set the title
        QQmlProperty::write(rootObject(), QString("titleText"), title.c_str());
    }

    void ProgressBar::advance(const double& step) {
        setProgress(mProgress + step);
    }

    void ProgressBar::setProgress(const double& progress) {
        mProgress = std::max(std::min(progress, mEnd), mStart);
        double progressInPercent = (mProgress - mStart) / (mEnd - mStart);
        // set the progress
        QQmlProperty::write(rootObject(), QString("currentProgress"), progressInPercent);

    }
}
