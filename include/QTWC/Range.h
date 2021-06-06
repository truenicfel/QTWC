#pragma once

#include <QWidget>

#include <string>

class QLineEdit;

namespace QTWC {

    /**
     * Range QWidget.
     *
     * This widget allows to select a range.
     */
    class Range: public QWidget {

        Q_OBJECT

    public:

        /**
         * Create the range widget.
         *
         * @param title of the widget.
         */
        explicit Range(const std::string& title);

        ~Range() override = default;

    private:

        QLineEdit* mLowerEdit;

        QLineEdit* mUpperEdit;

        /**
         * Helper to initialize the range widget.
         */
        void initialize(const std::string& title);

    };

}