#pragma once

#include <QSlider>

namespace QTWC {

	/**
	 * Extension to QSlider to allow for floating point sliders.
	 * 
	 * Note: 
	 *	Although some safety measures are implemented it might not be possible
	 *  to use all the slider modification methods available in QSlider. setRange
	 *  and setTickPosition should be safe to use. All others that influence the
	 *	slider range and values might be unsafe.
	 */
	class FPSlider: public QSlider {

		Q_OBJECT

	public:

		/**
		 * Create floating point slider.
		 *
		 * Same as constructor from QSlider with same signature.
		 *
		 * This initializes the slider to a 0.0 - 1.0 range with step size 0.01.
		 *
		 * @param orientation horizontal or vertical slider.
		 * @param parent pointer to the parent widget.
		 */
		FPSlider(Qt::Orientation orientation, QWidget* parent = nullptr);

		/**
		 * Create floating point slider.
		 *
		 * Same as constructor from QSlider with same signature.
		 *
		 * This initializes the slider to a 0.0 - 1.0 range with step size 0.01.
		 *
		 * @param parent pointer to the parent widget.
		 */
		FPSlider(QWidget* parent = nullptr);

		/**
		 * Create floating point slider.
		 *
		 * This initializes the slider according to the given parameters.
		 * 
		 * Usage example: 
		 *	- Want: Slider from 5 to 10 with step size 0.25
		 *  - Set: rangeBegin to 5, rangeEnd to 10 and stepSize to 0.25.
		 *
		 * @param orientation horizontal or vertical slider.
		 * @param rangeBegin: The lowest value of the slider (must be smaller than rangeEnd).
		 * @param rangeEnd: The largest value of the slider.
		 * @param stepSize: The size of one step of the slider (must be smaller than or equal to rangeEnd-rangeBegin).
		 * @param parent pointer to the parent widget.
		 */
		FPSlider(Qt::Orientation orientation, int rangeBegin, int rangeEnd, 
			float stepSize, QWidget* parent = nullptr);

		/**
		 * Get the current slider value.
		 *
		 * @return the current slider value.
		 */
		float getCurrentValue();

		/**
		 * Set the current slider value.
		 *
		 * @param value the value to set (illegal values get clamped).
		 */
		void setCurrentValue(float value);

		virtual ~FPSlider() = default;

		FPSlider(const FPSlider&) = default;

		FPSlider(FPSlider&&) = default;

		FPSlider& operator=(const FPSlider&) = default;

		FPSlider& operator=(FPSlider&&) = default;

	signals:

		/**
		 * Same as valueChanged(int) of qslider but with floating point value.
		 *
		 * @param value the value that the slider changed to.
		 */
		void fpValueChanged(float value);

	private slots:

		/**
		 * Slot for receiving the changed value of the underlying normal slider.
		 *
		 * @param value the value of the slider
		 */
		void receiveValueChanged(int value);

		/**
		 * Slot for receiving changes in the range of the slider.
		 *
		 * This is mostly a safety measure in case someone decides to change the sliders range
		 * afterwards.
		 *
		 * @param min minimum value of the slider.
		 * @param max maximum value of the slider.
		 */
		void receiveRangeChanged(int min, int max);


	private:

		/**
		 * Helper for initializing.
		 *
		 * Default initialization:
		 * --- range: 0-100
		 * --- step size: 1
		 * --- ticks: both sides:
		 * --- divisor: 100
		 */
		void initializeFPSlider();

		/**
		 * Helper for initializing.
		 *
		 * Manual initialization.
		 *
		 * @param rangeEnd the upper end of the slider.
		 */
		void initializeFPSlider(int rangeEnd);

		/**
		 * Helper to wrap various calls to connect().
		 */
		void setupConnections();


		/**
		 * The step size.
		 */
		float mStepSize;

		/**
		 * The lowest value of the slider.
		 */
		int mRangeBegin;

	};
}

