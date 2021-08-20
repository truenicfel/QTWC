#include <QQuickWidget>

namespace QTWC {

	/**
	 * A slider with two handles.
	 *
	 * A range slider implementation based on QML. To display
	 * the QML this class uses a QQuickWidget.
	 */
	class RangeSlider : public QQuickWidget {

		Q_OBJECT

	public:

		/**
		 * Constructor for range slider.
		 *
		 * @param rangeBegin
		 * @param rangeEnd
		 * @param title
		 * @param orientation vertical or horizontal
		 */
        RangeSlider(double rangeBegin, double rangeEnd, const std::string& title, Qt::Orientation orientation = Qt::Orientation::Horizontal);

		~RangeSlider() override = default;

    signals:

        /**
         * Emitted when a valid input is given in the range.
         *
         * @param lowerBound lowerBound of the range.
         * @param upperBound upperBound of the range.
         */
        void rangeChanged(const double& lowerBound, const double& upperBound);

	private slots:

	    /**
	     * To receive the signal when the right slider moves.
	     *
	     * @param value
	     */
	    void rightMoved(double value);

	    /**
	     * To receive the signal when the left slider moves.
	     *
	     * @param value
	     */
	    void leftMoved(double value);

	};

}