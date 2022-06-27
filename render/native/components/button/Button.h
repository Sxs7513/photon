#pragma once
#include <QPushButton>
#include <QDebug>

#include "components/flexLayout/FlexLayout.h"
#include "core/widget/Widget.h"
#include "core/flexUtils/FlexUtils.h"

class SButton : public QPushButton, public CoreWidget {
  Q_OBJECT
 public:
  SET_YOGA_COMP_Q_PROPERTIES
  using QPushButton::QPushButton;

  SButton(QWidget *parentWidget = nullptr);

  bool event(QEvent* e) override;
};
