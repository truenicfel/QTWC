#pragma once

#include "QTWC/Range.h"

namespace QTWC {

    /**
     * Specialization of QTWC::Range.
     *
     * Reimplemements Range such that only integers are valid
     * input. Additionally it is possible to set a maximum size
     * for the range.
     *
     * Furthermore it is enforced that lower bound will always be smaller
     * than upper bound.
     */
    class IntRange: public Range {

        Q_OBJECT

    public:

        /**
         * Construct the int range.
         *
         * @param title displayed title of widget.
         */
        IntRange(const std::string& title);

        /**
         * Construct int range.
         *
         * @param title displayed title of widget.
         * @param minimum lower bound of range.
         * @param maximum upper bound of range.
         */
        IntRange(const std::string& title, int minimum, int maximum);

        ~IntRange() override = default;

    signals:

        /**
         * Emitted when a valid input is given in the range.
         *
         * @param lowerBound lowerBound of the range.
         * @param upperBound upperBound of the range.
         */
        void intRangeChanged(const int& lowerBound, const int& upperBound);

    private slots:

        /**
         * This is connected to the underlying Range::rangeChanged method.
         *
         * When this is called we know that a "valid" (two ints within bounds
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

        void intRangeSetupConnections();

        // style sheets
        const static QString LINE_EDIT_BLACK_STYLESHEET;
        const static QString LINE_EDIT_RED_STYLESHEET;

    };

}


