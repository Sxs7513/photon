#include "Input.hpp"

SInput::SInput(QWidget *parentWidget): QTextEdit(parentWidget) {
    flexutils::configureFlexNode(this, this->getFlexNode(), true);
    this->connectSignal();
};

void SInput::connectSignal () {
    QObject::connect(this, &QTextEdit::textChanged, [=]() {
        if (this->EventWidget::isEventRegist("textChange")) {
            char* uid;
            QStringToChar(this->objectName(), &uid);
            this->EventWidget::event(nullptr, uid, "textChange", (QObject*)this);
        }
    });
};