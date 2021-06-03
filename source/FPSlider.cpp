#include "QTWC/FPSlider.h"

#include <exception>

#include <QSignalBlocker>

namespace QTWC {

	FPSlider::FPSlider(Qt::Orientation orientation, QWidget* parent) 
		: QSlider(orientation, parent)
		, mStepSize(1.0)
	{
		initializeFPSlider();
		setupConnections();
	}

	FPSlider::FPSlider(QWidget* parent)
		: QSlider(parent)
		, mStepSize(1.0)
	{
		initializeFPSlider();
		setupConnections();
	}

	FPSlider::FPSlider(Qt::Orientation orientation, float rangeBegin, float rangeEnd,
		float stepSize, QWidget* parent)
		: QSlider(orientation, parent)
		, mStepSize(stepSize)
		, mRangeBegin(rangeBegin)
	{
		initializeFPSlider(rangeEnd);
		setupConnections();
	}

	void FPSlider::initializeFPSlider() {
		this->setRange(0, 100);
		this->setTickInterval(1);
		this->setTickPosition(QSlider::TickPosition::TicksBothSides);
		mStepSize = 0.01;
	}

	void FPSlider::initializeFPSlider(float rangeEnd) {
		if (mRangeBegin >= rangeEnd) {
			throw std::invalid_argument("rangeBegin must be smaller than rangeEnd!");
		}
		if (mStepSize > (rangeEnd - mRangeBegin)) {
			throw std::invalid_argument("Step size must be smaller or equal to interval length!");
		}
		// compute length of underlying slider
		int length = static_cast<int>((rangeEnd - mRangeBegin) / mStepSize);
		// always start from 0
		this->setRange(0, length);
		this->setTickInterval(1);
		this->setTickPosition(QSlider::TickPosition::TicksBothSides);
	}

	void FPSlider::setupConnections() {
		// connect valueChanged of underlying slider with receiveValueChanged to make it a float value
		connect(this, &QSlider::valueChanged, this, &FPSlider::receiveValueChanged);
		// connect rangeChanged of underlying slider with receiveRangeChanged to adapt FPSlider
		connect(this, &QSlider::rangeChanged, this, &FPSlider::receiveRangeChanged);
	}

	void FPSlider::receiveValueChanged(int value) {
		// recalculate and emit
		float floatValue = mRangeBegin + (value * mStepSize);
		emit fpValueChanged(floatValue);
	}

	void FPSlider::receiveRangeChanged(int min, int max) {
		// we will adapt the range in the same way as the slider was initialized
		{
			const QSignalBlocker blocker(this);
			mRangeBegin = min;
			initializeFPSlider(max);
		}
	}

	float FPSlider::getCurrentValue() {
		return mRangeBegin + (this->value() * mStepSize); 
	}

	void FPSlider::setCurrentValue(float value) {
		// subtract such that value is within underlying slider range
		// set value takes care of clamping
		this->setValue(static_cast<int>((value - mRangeBegin) / mStepSize));
	}

}


