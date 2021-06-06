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
         * This will be called whenever one of the line edits
         * registered a change in its text.
         */
        void textBoxChanged();

    protected:

        QLineEdit* getLowerEdit();

        QLineEdit* getUpperEdit();

    private:

        QLineEdit* mLowerEdit;

        QLineEdit* mUpperEdit;

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