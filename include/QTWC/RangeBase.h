#pragma once

#include <QWidget>
#include <QLocale>

#include <string>

class QLineEdit;

namespace QTWC {

    /**
     * RangeBase QWidget.
     *
     * This widget allows to select a range. If the range should be
     * submitted return must be pressed.
     */
    class RangeBase: public QWidget {

        Q_OBJECT

    public:

        /**
         * Create the range widget.
         *
         * @param title of the widget.
         * @param locale redefine this if something else is needed.
         */
        explicit RangeBase(const std::string& title, const QLocale& locale = QLocale::c());

        ~RangeBase() override = default;

    signals:

        /**
         * This is emitted whenever the specified range changes.
         *
         * @param lowerBound the current lower bound.
         * @param upperBound the current upper bound.
         */
        void rangeChanged(const QString& lowerBound, const QString& upperBound);

    private slots:

        /**
         * This will be called whenever the user pressed return on one of the line
         * edits.
         */
        void userPressedReturn();

    protected:

        QLineEdit* getLowerEdit();

        QLineEdit* getUpperEdit();

        QLocale getLocale();

    private:

        QLineEdit* mLowerEdit;

        QLineEdit* mUpperEdit;

        QLocale mLocale;

        /**
         * Helper to initialize the range widget.
         */
        void initialize(const std::string& title);

        /**
         * Helper to setup connections from text boxes
         * to methods.
         */
        void setupConnections();

    };

}