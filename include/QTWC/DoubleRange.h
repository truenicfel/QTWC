#pragma once

#include "QTWC/Range.h"

namespace QTWC {

    /**
     * Specialization of QTWC::Range.
     *
     * Reimplemements Range such that only doubles are valid
     * input. Additionally it is possible to set a maximum size
     * for the range.
     *
     * Furthermore it is enforced that lower bound will always be smaller
     * than upper bound.
     */
    class DoubleRange: public Range {

        Q_OBJECT

    public:

        /**
         * Construct the double range.
         *
         * Note: All available parameters in the other constructor
         * are set to default values in this one. Meaning that
         * all double numbers are allowed with up to 1000 decimal
         * digits after the decimal point.
         *
         * @param title displayed title of widget.
         * @param locale redefine this if something else is needed.
         */
        explicit DoubleRange(const std::string& title, const QLocale& locale = QLocale::c());

        /**
         * Construct double range.
         *
         * @param title displayed title of widget.
         * @param minimum lower bound of range.
         * @param maximum upper bound of range.
         * @param decimals the number of digits after the decimal point
         * @param locale redefine this if something else is needed.
         */
        DoubleRange(const std::string& title, double minimum, double maximum, int decimals, const QLocale& locale = QLocale::c());

        ~DoubleRange() override = default;

        void setDoubleRange(double lower, double upper);

    signals:

        /**
         * Emitted when a valid input is given in the range.
         *
         * @param lowerBound lowerBound of the range.
         * @param upperBound upperBound of the range.
         */
        void doubleRangeChanged(const double& lowerBound, const double& upperBound);

    private slots:

        /**
         * This is connected to the underlying Range::rangeChanged method.
         *
         * When this is called we know that a "valid" (two doubles within bounds
         * detected). Additional checks are required to ensure that lowerBound
         * is smaller than upperBound.
         *
         * @param lowerBound the specified lower bound.
         * @param upperBound the specified upper bound.
         */
        void receiveValidatedRangeChange(const QString& lowerBound, const QString& upperBound);

    private:

        /**
         * States if the color of the line edits is red currently.
         */
        bool mInvalid;

        void doubleRangeSetupConnections();

        // style sheets
        const static QString LINE_EDIT_BLACK_STYLESHEET;
        const static QString LINE_EDIT_RED_STYLESHEET;

    };

}


