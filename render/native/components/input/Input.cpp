#include "Input.hpp"

SInput::SInput(QWidget *parentWidget): QTextEdit(parentWidget) {
    flexutils::configureFlexNode(this, this->getFlexNode(), true);
};

void SInput::connectSignalsToEventEmitter () {
    QObject::connect(this, &QTextEdit::textChanged, [=]() {
        
    });
};