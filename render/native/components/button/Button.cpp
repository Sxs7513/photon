#include "Button.h"

SButton::SButton(QWidget *parentWidget): QPushButton(parentWidget) {
    flexutils::configureFlexNode(this, this->getFlexNode(), true);
};

static std::map<QEvent::Type, std::string> supportEvents {
  { QEvent::MouseButtonPress, "click" },
};

bool SButton::event (QEvent* e) {
    std::map<QEvent::Type, std::string>::iterator iter;
    if ((iter = supportEvents.find(e->type())) != supportEvents.end()) {
        if (this->EventWidget::isEventRegist(iter->second)) {
            QString str1 = this->objectName();
            QByteArray ba = str1.toLocal8Bit();
            const char *uid = ba.data();
            if (this->EventWidget::event(e, uid, iter->second)) {
                return true;
            }
        }
    }

    return this->QPushButton::event(e);
}
