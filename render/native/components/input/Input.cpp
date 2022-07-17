#include "Input.hpp"

SInput::SInput(QWidget *parentWidget): QLineEdit(parentWidget) {
    flexutils::configureFlexNode(this, this->getFlexNode(), true);
    this->connectSignal();
};

void SInput::connectSignal () {
    QObject::connect(this, &QLineEdit::textChanged, [=]() {
        if (this->EventWidget::isEventRegist("textChange")) {
            this->EventWidget::event(nullptr, this->objectName(), "textChange", (QObject*)this);
        }
    });
};

static std::map<QEvent::Type, std::string> supportEvents {
  { QEvent::FocusIn, "focus" },
  { QEvent::FocusOut, "blur" },
};

bool SInput::event(QEvent *e) {
    std::map<QEvent::Type, std::string>::iterator iter;

    if ((iter = supportEvents.find(e->type())) != supportEvents.end()) {
        if (this->EventWidget::isEventRegist(iter->second)) {
            if (this->EventWidget::event(e, this->objectName(), iter->second, (QObject*)this)) {
                return true;
            }
        }
    }

    return this->QWidget::event(e);
}