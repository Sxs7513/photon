#include "Text.h"

SLabel::SLabel(QWidget *parentWidget): QLabel(parentWidget) {
    flexutils::configureFlexNode(this, this->getFlexNode(), true);
};