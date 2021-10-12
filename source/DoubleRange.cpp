#include "QTWC/DoubleRange.h"

#include <QDoubleValidator>
#include <QLineEdit>
#include <QFont>

#include <limits>
#include <stdexcept>

namespace QTWC {

    const QString DoubleRange::LINE_EDIT_BLACK_STYLESHEET = "QLineEdit { color: black }";

    const QString DoubleRange::LINE_EDIT_RED_STYLESHEET = "QLineEdit { color: red }";

    DoubleRange::DoubleRange(const std::string& title, const QLocale& locale)
            : QTWC::RangeBase(title, locale)
            , mInvalid(false)

    {
        QDoubleValidator* validator = new QDoubleValidator(this);
        validator->setLocale(getLocale());
        validator->setNotation(QDoubleValidator::StandardNotation);
        getLowerEdit()->setValidator(validator);
        getUpperEdit()->setValidator(validator);
        doubleRangeSetupConnections();
    }

    DoubleRange::DoubleRange(const std::string &title, double minimum, double maximum, int decimals, const QLocale& locale)
        : QTWC::RangeBase(title, locale)
        , mInvalid(false)
    {
        QDoubleValidator* validator = new QDoubleValidator(minimum, maximum, decimals, this);
        validator->setLocale(getLocale());
        validator->setNotation(QDoubleValidator::StandardNotation);
        getLowerEdit()->setValidator(validator);
        getUpperEdit()->setValidator(validator);
        doubleRangeSetupConnections();
    }

    void DoubleRange::receiveValidatedRangeChange(const QString& lowerBound, const QString& upperBound) {
        // convert to int
        double lower = lowerBound.toDouble();
        double upper = upperBound.toDouble();

        // lower must be smaller than upper
        if (lower <= upper) {
            emit doubleRangeChanged(lower, upper);

            // if red previously we can change back to black
            if (mInvalid) {
                getLowerEdit()->setStyleSheet(LINE_EDIT_BLACK_STYLESHEET);
                getUpperEdit()->setStyleSheet(LINE_EDIT_BLACK_STYLESHEET);
                mInvalid = false;
            }

        } else {
            // range can't know which one is wrong so both will be
            getLowerEdit()->setStyleSheet(LINE_EDIT_RED_STYLESHEET);
            getUpperEdit()->setStyleSheet(LINE_EDIT_RED_STYLESHEET);
            mInvalid = true;
        }


    }

    void DoubleRange::doubleRangeSetupConnections() {
        // connect base class rangeChanged signal with this class receiveValidatedRangeChange
        // validation in this case only validates if the input is an int and
        // in case of specified bounds if this int is within those
        bool success = connect(this, &RangeBase::rangeChanged, this, &DoubleRange::receiveValidatedRangeChange);
        if (!success) {
            throw std::runtime_error("The connection did not work!");
        }
    }

    void DoubleRange::setDoubleRange(double lower, double upper) {
        getLowerEdit()->setText(getLocale().toString(lower));
        getUpperEdit()->setText(getLocale().toString(upper));
    }

    void DoubleRange::getCurrentRange(double& lower, double& upper) {
        lower = getLocale().toDouble(getLowerEdit()->text());
        upper = getLocale().toDouble(getUpperEdit()->text());
    }

}


