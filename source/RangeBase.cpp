#include "QTWC/RangeBase.h"

#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>

#include <stdexcept>

namespace QTWC {

    RangeBase::RangeBase(const std::string& title, const QLocale& locale)
            : mLowerEdit(nullptr) // initialized later
            , mUpperEdit(nullptr) // initialized later
            , mLocale(locale)
    {
        initialize(title);
        setupConnections();
    }

    void RangeBase::initialize(const std::string& title) {

        // the main layout of this widget:
        //  - title row with a title label in it (spanning 4 columns)
        //  - second row with 4 cells in it: Lower: <text box> Upper: text box
        QGridLayout* layout = new QGridLayout(this);
        layout->setVerticalSpacing(0);
        layout->setHorizontalSpacing(3);

        // title widget
        QLabel* titleLabel = new QLabel(tr(title.c_str()));
        titleLabel->setAlignment(Qt::AlignCenter);
        // spans 1 row and 4 cols
        layout->addWidget(titleLabel, 0, 0, 1 , 4);

        // widgets for second row
        QLabel* lowerLabel = new QLabel(tr("Lower:"));
        QLabel* upperLabel = new QLabel(tr("Upper:"));
        mLowerEdit = new QLineEdit();
        mUpperEdit = new QLineEdit();

        // alignment
        lowerLabel->setAlignment(Qt::AlignHCenter | Qt::AlignLeft);
        upperLabel->setAlignment(Qt::AlignHCenter | Qt::AlignLeft);

        // add to layout
        layout->addWidget(lowerLabel, 1, 0, 1, 1, Qt::AlignLeft | Qt::AlignVCenter);
        layout->addWidget(mLowerEdit, 1, 1, 1, 1, Qt::AlignCenter);
        layout->addWidget(upperLabel, 1, 2, 1, 1, Qt::AlignLeft | Qt::AlignVCenter);
        layout->addWidget(mUpperEdit, 1, 3, 1, 1, Qt::AlignCenter);
    }

    void RangeBase::setupConnections() {
        // listen to textEdited signal and both connected to textBoxChanged Method
        bool success = connect(mLowerEdit, &QLineEdit::returnPressed, this, &RangeBase::userPressedReturn);
        if (!success) {
            throw std::runtime_error("The connection did not work!");
        }
        success = connect(mUpperEdit, &QLineEdit::returnPressed, this, &RangeBase::userPressedReturn);
        if (!success) {
            throw std::runtime_error("The connection did not work!");
        }
    }

    void RangeBase::userPressedReturn() {
        emit rangeChanged(
                mLowerEdit->text(),
                mUpperEdit->text()
        );
    }

    QLineEdit* RangeBase::getLowerEdit() {
        return mLowerEdit;
    }

    QLineEdit* RangeBase::getUpperEdit() {
        return mUpperEdit;
    }

    QLocale RangeBase::getLocale() {
        return mLocale;
    }

}


