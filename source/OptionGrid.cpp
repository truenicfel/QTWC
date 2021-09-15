#include "QTWC/OptionGrid.h"

#include <QQuickWidget>
#include <QQmlProperty>
#include <QQuickItem>
#include <QGridLayout>

#include "QMLPaths.h"

#include <iostream>

namespace QTWC {

    OptionGrid::OptionGrid(int columns, int rows, const std::vector<std::string>& options)
    : mOptions()
    , mIdOption()
    , mLayout(new QGridLayout(this))
    , mColumns(columns)
    , mRows(rows)
    {

        int column = 0;
        int row = 0;

        for (const std::string& option: options) {

            if (column < mColumns && row < mRows) {
                addOption(column, row, option);
                column++;
                if (column % mColumns == 0) {
                    column = 0;
                    row++;
                }
            }

        }

    }

    void OptionGrid::stateChanged(int id, bool state) {
        emit optionChangedState(mIdOption[id], state);
    }

    void OptionGrid::addOption(int column, int row, const std::string& option) {

        auto* newSwitch = new QQuickWidget();

        newSwitch->setResizeMode(QQuickWidget::SizeRootObjectToView);
        newSwitch->setSource(QUrl::fromLocalFile(OPTION_GRID_QML));

        QQmlProperty::write(newSwitch->rootObject(), "optionText", option.c_str());
        int id = (row * mColumns) + column;
        QQmlProperty::write(newSwitch->rootObject(), "identificator", id);
        QQmlProperty::write(newSwitch->rootObject(), "checked", true);

        mLayout->addWidget(newSwitch, row, column);

        bool success = QObject::connect(newSwitch->rootObject(), SIGNAL(stateChanged(int,bool)), this, SLOT(stateChanged(int,bool)));
        if (!success) {
            throw std::runtime_error("The connection between state changes and slot did not work!");
        }

        mOptions[option] = newSwitch;
        mIdOption[id] = option;
    }

    void OptionGrid::setState(const std::string& option, bool newState) {
        QQmlProperty::write(mOptions[option]->rootObject(), "checked", newState);
    }

    void OptionGrid::setFontSize(double fontSize) {
        for (auto& mOption : mOptions) {
            QQmlProperty::write(mOption.second->rootObject(), "fontSize", fontSize);
        }
    }

}