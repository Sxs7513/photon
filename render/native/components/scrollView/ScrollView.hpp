#pragma once

#include <QScrollArea>
#include <QWidget>
#include <QString>
#include <QDebug>
#include <QPainter>
#include <QStyle>
#include <QStylePainter>
#include <QStyleOption>
#include <QScrollBar>

#include <stdlib.h>

#include "components/Components.h"
#include "components/flexLayout/FlexLayout.h"
#include "components/view/View.hpp"
#include "core/widget/Widget.h"
#include "core/flexUtils/FlexUtils.h"

#include "deps/yoga/YGNode.h"

class SScrollArea : public QScrollArea, public CoreWidget {
    Q_OBJECT
    SET_YOGA_COMP_Q_PROPERTIES

  public:
    using QScrollArea::QScrollArea;
    SWidget* root = nullptr;

    SScrollArea(QWidget *parentWidget = nullptr);
    ~SScrollArea();

    void appendChild(void* child, void* flexNode);
    void removeChild(void* child, void* flexNode);
    void insertChildBefore(void *childWidget, void* beforeChildNode, void* childNode);
    void setFlexNodeSizeControlled(bool isSizeControlled);
    void enableHorizontal(bool payload);
    void enableVertical(bool payload);
};