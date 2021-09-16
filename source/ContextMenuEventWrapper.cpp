#include "QTWC/ContextMenuEventWrapper.h"

namespace QTWC {

    void ContextMenuEventWrapper::contextMenuEvent(QContextMenuEvent* event) {
        emit contextMenuEventSignal(event);
    }

}


