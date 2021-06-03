#include "QTWC/FancySlider.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>

#include <sstream>
#include <iomanip>

namespace QTWC {

	FancySlider::FancySlider(float rangeBegin, float rangeEnd, float stepSize, const std::string& title)
		: mSlider(new FPSlider(Qt::Orientation::Horizontal, rangeBegin, rangeEnd, stepSize))
		, mValueDisplay(new QLabel())
		, mValueDisplaySubstringLength(4)
	{
		// outer layout
		QVBoxLayout* outerLayout = new QVBoxLayout(this);
		// remove spacings such that the sliders widgets will be more tightly together
		outerLayout->setSpacing(0);

		// title label (first row of outerLayout)
		QLabel* titleLabel = new QLabel(tr(title.c_str()));
		titleLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
		
		// second row of outer layout root widget
		QWidget* secondRowRootWidget = new QWidget();
		// this will be added to outer layout alongside title
		outerLayout->addWidget(titleLabel);
		outerLayout->addWidget(secondRowRootWidget);

		// second row root widget will be the parent widget for the horizontal layout
		QHBoxLayout* inner = new QHBoxLayout(secondRowRootWidget);
		// this will contain the slider and a qlabel which displays the current slider value
		// the initial text is the inital value but only 4 digits
		// in case the step size is exceptionally small this is modified
		if (stepSize < 0.001) {
			mValueDisplaySubstringLength = 8;
			// modify the font to accomadate larger value
			QFont valueDisplayFont = mValueDisplay->font();
			valueDisplayFont.setPointSize(7);
			mValueDisplay->setFont(valueDisplayFont);
		}
		std::string initialText = std::to_string(mSlider->getCurrentValue());
		initialText = initialText.substr(0, mValueDisplaySubstringLength);
		mValueDisplay->setText(tr(initialText.c_str()));
		
		// now add the widgets
		inner->addWidget(mSlider);
		inner->addWidget(mValueDisplay);

		// set a maximum height of 80 such that the widgets are tightly together
		this->setMaximumHeight(80);

		// connect slider value changed with slot updateDisplay
		bool success = QObject::connect(mSlider, &QTWC::FPSlider::fpValueChanged, this, &FancySlider::updateValueDisplay);
		if (!success) {
			throw std::runtime_error("The connection between slider value changes and update value did not work!");
		}
	}

	FPSlider* FancySlider::getSlider() {
		return mSlider;
	}

	void FancySlider::updateValueDisplay(float value) {
		// cut 4 digits
		std::string text = std::to_string(value);
		text = text.substr(0, mValueDisplaySubstringLength);
		mValueDisplay->setText(tr(text.c_str()));
		mValueDisplay->update();
	}

}