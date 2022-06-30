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