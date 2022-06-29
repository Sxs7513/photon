#pragma once
#include <QLabel>

#include "core/Widget/Widget.h"

class SLabel : public QLabel, public CoreWidget {
  Q_OBJECT

 public:
  SET_YOGA_COMP_Q_PROPERTIES
  using QLabel::QLabel;
  SLabel(QWidget *parentWidget = nullptr);

};
