#include "ScrollView.hpp"

SScrollArea::SScrollArea(QWidget *parentWidget): QScrollArea(parentWidget) {
    flexutils::configureFlexNode(this, this->getFlexNode(), false);
    if (this->root == nullptr) {
        // this->root = new SWidget;
        // YGNodeInsertChild(this->getFlexNode(), this->root->getFlexNode(), 0);
        // this->root->setStyleSheet("width: 500px; qproperty-yWidth: 500px");
    }
};

void SScrollArea::enableHorizontal(bool payload) {
    this->horizontalScrollBar()->setEnabled(payload);
};

void SScrollArea::enableVertical(bool payload) {
    this->verticalScrollBar()->setEnabled(payload);
};

void SScrollArea::insertChildBefore(void *child, void* beforeChildNode, void* childNode) {
    if (this->root != nullptr) {
        this->root->insertChildBefore(child, beforeChildNode, childNode);
    }
};

void SScrollArea::removeChild(void* child, void* flexNode) {
    // if (this->root != nullptr) {
    //     this->root->removeChild(child, flexNode);
    // }
};

void SScrollArea::appendChild (void* child, void* flexNode) {
    YGNodeInsertChild(this->getFlexNode(), static_cast<YGNodeRef>(flexNode), 0);
    this->setWidget(static_cast<QWidget*>(child));
    // if (this->root != nullptr) {
    //     this->root->appendChild(child, flexNode);
    // }
};

void SScrollArea::setFlexNodeSizeControlled(bool isSizeControlled) {
    YGNodeRef node = this->getFlexNode();
    FlexNodeContext* ctx = flexutils::getFlexNodeContext(node);
    ctx->isSizeControlled = isSizeControlled;
};

SScrollArea::~SScrollArea () {
    // delete this->layout;
}