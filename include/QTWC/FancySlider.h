#include <QWidget>

#include <string>

#include "QTWC/FPSlider.h"

class QVBoxLayout;
class QLabel;

namespace QTWC {

	/**
	 * Wrapper for a FPSlider.
	 *
	 * Shows the current value of the slider in a textbox and
	 * gives the slider a title.
	 *
	 * This uses the FPSlider and height is set to a maximum of 80.
	 */
	class FancySlider : public QWidget {

		Q_OBJECT

	public:

		/**
		 * Constructor for fancy slider.
		 *
		 * @param rangeBegin see FPSlider
		 * @param rangeEnd see FPSlider
		 * @param stepSize see FPSlider
		 */
		FancySlider(int rangeBegin, int rangeEnd, float stepSize, const std::string&);

		~FancySlider() = default;

		/**
		 * Get the slider for setting up connections.
		 *
		 * @return the slider.
		 */
		FPSlider* getSlider();

	private slots:

		void updateValueDisplay(float value);

	private:

		/**
		 * The slider used.
		 */
		FPSlider* mSlider;

		/**
		 * Displays the current slider value.
		 */
		QLabel* mValueDisplay;

	};

}