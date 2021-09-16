#pragma once

#include <QWidget>

namespace QTWC {

    /**
     * This wraps a widget and emits a signal whenever a contextMenuEvent occurred.
     */
    class ContextMenuEventWrapper: public QWidget {

        Q_OBJECT

    public:

        ContextMenuEventWrapper() = default;

        ~ContextMenuEventWrapper() override = default;

    protected:
        /**
         * Reimplemented from QWidget.
         *
         * This does everything this class has to offer.
         *
         * @param event
         */
        void contextMenuEvent(QContextMenuEvent* event) override;

    signals:

        /**
         * Emitted when a context menu event occurred on this widget.
         *
         * @param contextMenuEvent the event
         */
        void contextMenuEventSignal(QContextMenuEvent* contextMenuEvent);

    };

}


