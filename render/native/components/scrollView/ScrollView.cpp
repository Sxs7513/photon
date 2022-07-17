#include "ScrollView.hpp"

SScrollArea::SScrollArea(QWidget *parentWidget): QScrollArea(parentWidget) {
    flexutils::configureFlexNode(this, this->getFlexNode(), false);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setFrameShape(QFrame::NoFrame);

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

};

void SScrollArea::removeChild() {
    this->setWidget(nullptr);
};

void SScrollArea::appendChild (void* child, void* flexNode) {
    if (this->childWrapper != nullptr) {
        delete this->childWrapper;
    }
    this->child = (SWidget*)child;
    this->childWrapper = new SWidget();
    this->childWrapper->setFlexNode(this->getFlexNode());
    this->childWrapper->appendChild((void*)(this->child), (void*)(this->child->getFlexNode()));
    this->setWidget(static_cast<QWidget*>(childWrapper));
};

void SScrollArea::resetChild () {
    this->child->setParent(nullptr);
    if (this->childWrapper != nullptr) {
        delete this->childWrapper;
    }
    this->childWrapper = new SWidget();
    this->childWrapper->setFlexNode(this->getFlexNode());
    this->childWrapper->appendChild((void*)(this->child), (void*)(this->child->getFlexNode()));
    this->setWidget(static_cast<QWidget*>(childWrapper));
};

void SScrollArea::setFlexNodeSizeControlled(bool isSizeControlled) {
    YGNodeRef node = this->getFlexNode();
    FlexNodeContext* ctx = flexutils::getFlexNodeContext(node);
    ctx->isSizeControlled = isSizeControlled;
};

SScrollArea::~SScrollArea () {
    // delete this->layout;
}