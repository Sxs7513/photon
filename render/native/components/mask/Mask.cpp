#include "Mask.hpp"

SMask::SMask(QWidget *parentWidget): QWidget(parentWidget) {};

void SMask::showEvent(QShowEvent* event) {
    if (this->parentWidget() == nullptr) {
        return;
    }
    this->setStyleSheet(this->styleSheet != nullptr ? this->styleSheet : "background-color:rgba(0,0,0,0)");
    this->setGeometry(0, 0, this->parentWidget()->width(), this->parentWidget()->height());
}