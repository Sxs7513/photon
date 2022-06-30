#include "Input.hpp"

STextarea::STextarea(QWidget *parentWidget): QTextEdit(parentWidget) {
    flexutils::configureFlexNode(this, this->getFlexNode(), true);
    this->connectSignal();
};

void STextarea::connectSignal () {
    QObject::connect(this, &QTextEdit::textChanged, [=]() {
        if (this->EventWidget::isEventRegist("textChange")) {
            this->EventWidget::event(nullptr, this->objectName(), "textChange", (QObject*)this);
        }
    });
};