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
            , mValidator(new QIntValidator(this))
            , mMinimum(std::numeric_limits<int>::min())
            , mMaximum(std::numeric_limits<int>::max())
            , mRedLower(false)
            , mRedUpper(false)

    {
        getLowerEdit()->setValidator(mValidator);
        intRangeSetupConnections();
    }

    IntRange::IntRange(const std::string &title, int minimum, int maximum)
        : QTWC::Range(title)
        , mValidator(new QIntValidator(minimum, maximum, this))
        , mMinimum(minimum)
        , mMaximum(maximum)
        , mRedLower(false)
        , mRedUpper(false)
    {
        getLowerEdit()->setValidator(mValidator);
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
            if (mRedLower) {
                getLowerEdit()->setStyleSheet(LINE_EDIT_BLACK_STYLESHEET);
            }
            if (mRedUpper) {
                getUpperEdit()->setStyleSheet(LINE_EDIT_BLACK_STYLESHEET);
            }
        } else {
            // range can't know which one is wrong so both will be
            changeFontToRed(getLowerEdit());
            changeFontToRed(getUpperEdit());
        }


    }

    void IntRange::changeFontToRed(QLineEdit* lineEdit) {
        lineEdit->setStyleSheet(LINE_EDIT_RED_STYLESHEET);
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


