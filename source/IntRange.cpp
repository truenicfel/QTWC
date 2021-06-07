#include "QTWC/IntRange.h"

#include <QIntValidator>
#include <QLineEdit>
#include <QFont>

#include <limits>

namespace QTWC {

    const QString IntRange::LINE_EDIT_BLACK_STYLESHEET = "QLineEdit { color: black }";

    const QString IntRange::LINE_EDIT_RED_STYLESHEET = "QLineEdit { color: red }";

    IntRange::IntRange(const std::string& title)
            : QTWC::Range(title)
            , mInvalid(false)

    {
        QIntValidator* validator = new QIntValidator(this);
        getLowerEdit()->setValidator(validator);
        intRangeSetupConnections();
    }

    IntRange::IntRange(const std::string &title, int minimum, int maximum)
        : QTWC::Range(title)
        , mInvalid(false)
    {
        QIntValidator* validator = new QIntValidator(minimum, maximum, this);
        getLowerEdit()->setValidator(validator);
        intRangeSetupConnections();
    }

    void IntRange::receiveValidatedRangeChange(const QString& lowerBound, const QString& upperBound) {
        // convert to int
        int lower = lowerBound.toInt();
        int upper = upperBound.toInt();

        // lower must be smaller than upper
        if (lower <= upper) {
            emit intRangeChanged(lower, upper);

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

    void IntRange::intRangeSetupConnections() {
        // connect base class rangeChanged signal with this class receiveValidatedRangeChange
        // validation in this case only validates if the input is an int and
        // in case of specified bounds if this int is within those
        bool success = connect(this, &Range::rangeChanged, this, &IntRange::receiveValidatedRangeChange);
        if (!success) {
            throw std::runtime_error("The connection did not work!");
        }
    }

}


