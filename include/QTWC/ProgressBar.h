#include <QQuickWidget>

#include <string>

namespace QTWC {

	/**
	 * A progress bar.
	 *
	 * The progress bar shows the progress on a bar and additionally in percent
	 * below it.
	 */
	class ProgressBar : public QQuickWidget {

		Q_OBJECT

	public:

		/**
		 * Constructor for ProgressBar.
		 *
		 * end - start will give the total range of the bar.
		 *
		 * @param start
		 * @param end
		 * @param title displayed above the progress bar
		 */
        ProgressBar(const double& start, const double& end, const std::string& title);

		~ProgressBar() override = default;

        /**
         * Advance the progress bar by the given step.
         *
         * If current progress + step exceeds the end of the progress bar it will be clamped to end.
         *
         * @param step
         */
        void advance(const double& step);

        /**
         * Set the progress.
         *
         * If progress is larger than end or smaller than start it will be clamped.
         *
         * @param progress
         */
        void setProgress(const double& progress);

    private:

        double mStart;

        double mEnd;

        double mProgress;

	};

}