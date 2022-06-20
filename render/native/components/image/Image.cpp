#include "Image.h"

SImage::SImage(QWidget *parentWidget): QLabel(parentWidget) {
    flexutils::configureFlexNode(this, this->getFlexNode(), true);
};