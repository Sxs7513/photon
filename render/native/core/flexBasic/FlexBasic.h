#pragma once
#include <QWidget>
#include "deps/yoga/YGNode.h"

#include "core/FlexUtils/FlexUtils.h"

class FLexBasic {
  YGNodeRef node;

 public:
  FLexBasic();
  YGNodeRef getFlexNode() const;
  void setFlexNode(YGNodeRef node);
  ~FLexBasic();
};