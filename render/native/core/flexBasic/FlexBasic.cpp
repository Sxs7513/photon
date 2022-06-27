#include "FlexBasic.h"

#include <stdlib.h>

FLexBasic::FLexBasic() {
  this->node = YGNodeNew(); 
}

YGNodeRef FLexBasic::getFlexNode() const { return this->node; }
void FLexBasic::setFlexNode(YGNodeRef node) { this->node = node; };

FLexBasic::~FLexBasic() {
  FlexNodeContext* ctx = flexutils::getFlexNodeContext(this->node);
  if (ctx != nullptr) {
    delete ctx;
  };
  YGNodeFree(this->node);
}