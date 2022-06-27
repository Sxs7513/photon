#pragma once

#include <QLayout>
#include <QWidget>
#include <QTimer>

#include "deps/yoga/YGNode.h"

class FlexLayout : public QLayout {
  Q_OBJECT
 private:
  YGNodeRef node;
  YGNodeRef getRootNode(YGNodeRef node) const;
  void calculateLayout() const;

  // performance memebers
  QTimer throttleTimer;
  QRect cachedRect;
  // end of performance memeber
 private slots:
  void performLayout();

 public:
  FlexLayout(QWidget *parentWidget = nullptr, YGNodeRef parentNode = nullptr);
  ~FlexLayout() override;
  QSize sizeHint() const override;
  QSize minimumSize() const override;
  void addItem(QLayoutItem *) override;
  QLayoutItem *itemAt(int index) const override;
  QLayoutItem *takeAt(int index) override;
  int count() const override;
  void addWidget(QWidget *childWidget, YGNodeRef childNode);
  void removeWidget(QWidget *childWidget, YGNodeRef childNode);
  void setGeometry(const QRect &rect) override;
  void setFlexNode(YGNodeRef parentNode);
  bool hasHeightForWidth() const override;
  void insertChildBefore(QWidget* childWidget, YGNodeRef beforeChildNode, YGNodeRef childNode);
};

