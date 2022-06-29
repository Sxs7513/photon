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
            char* uid;
            QStringToChar(this->objectName(), &uid);
            if (this->EventWidget::event(e, uid, iter->second, (QObject*)this)) {
                return true;
            }
        }
    }

    return this->QPushButton::event(e);
}
