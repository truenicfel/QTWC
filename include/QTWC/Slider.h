#include <QQuickWidget>

namespace QTWC {

	/**
	 * A slider.
	 *
	 * A slider implementation based on QML. To display
	 * the QML this class uses a QQuickWidget.
	 *
	 * Currently only a horizontal implementation is available.
	 */
	class Slider : public QQuickWidget {

		Q_OBJECT

	public:

		/**
		 * Constructor for range slider.
		 *
		 * @param rangeBegin
		 * @param rangeEnd
		 * @param title
		 */
        Slider(double rangeBegin, double rangeEnd, const std::string& title);

		~Slider() override = default;

    signals:

        /**
         * Emitted when a valid input is given in the range.
         *
         * @param value slider position
         */
        void sliderValueChanged(const double& value);

	private slots:

        void receiveMoved(const double& value);

	};

}