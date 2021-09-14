#include <QWidget>

#include <vector>
#include <string>
#include <map>

class QQuickWidget;
class QGridLayout;

namespace QTWC {

	/**
	 * A grid of options.
	 *
	 * This uses the qml Switch and the QGridLayout
	 */
	class OptionGrid : public QWidget {

		Q_OBJECT

	public:

	    /**
	     * Constructor for the option grid.
	     *
	     * The grid is static. The given column and row size can't be modified.
	     *
	     * Note: If more options are specified than columns * rows then these will be ignored.
	     *
	     * @param columns number of columns in the grid
	     * @param rows number of rows in the grid
	     * @param options the option names that should be displayed alongside each button
	     */
		OptionGrid(int columns, int rows, const std::vector<std::string>& options);

		~OptionGrid() override = default;

		/**
		 * Set the state of the given option.
		 *
		 * @param option
		 * @param newState
		 */
		void setState(const std::string& option, bool newState);

    signals:

	    /**
	     * This is the signal that is emitted when a state
	     * change of any of the options occurs.
	     *
	     * @param option which option had a state change
	     * @param newState what is the new sate of that option.
	     */
	    void optionChangedState(std::string option, bool newState);

	private slots:

	    void stateChanged(int id, bool state);

	private:

	    /**
	     * Stores the switch for each option provided in the constructor.
	     */
	    std::map<std::string, QQuickWidget*> mOptions;

	    /**
	     * Maps id to option name.
	     */
	    std::map<int, std::string> mIdOption;

	    /**
	     * Stores the layout where the quick widgets are stored in.
	     */
        QGridLayout* mLayout;

        /**
         * Store dimension of grid.
         */
        int mColumns;
        int mRows;

        /**
         * Small helper to add an option to mOptions and mLayout.
         * @param column
         * @param row
         * @param option
         */
	    void addOption(int column, int row, const std::string& option);

	};

}