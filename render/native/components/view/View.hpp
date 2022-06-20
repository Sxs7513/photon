#pragma once
#include <QPainter>
#include <QStyle>
#include <QStylePainter>
#include <QStyleOption>
#include <QWidget>

#include "components/flexLayout/FlexLayout.h"
#include "core/widget/Widget.h"
#include "core/flexUtils/FlexUtils.h"

#include <QDebug>

class SWidget : public QWidget, public CoreWidget {
  Q_OBJECT
  SET_YOGA_COMP_Q_PROPERTIES
 private:
  FlexLayout* layout = nullptr;
 public:
  using QWidget::QWidget;

  void paintEvent(QPaintEvent* e) override {
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    QWidget::paintEvent(e);
  }

  SWidget(QWidget *parentWidget = nullptr);
  ~SWidget();
  void appendChild(void* child, void* flexNode);
  void removeChild(void* child, void* flexNode);
  void insertChildBefore(void *childWidget, void* beforeChildNode, void* childNode);
  void setFlexNodeSizeControlled(bool isSizeControlled);
  bool event(QEvent *e) override;
};