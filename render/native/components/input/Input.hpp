#pragma once

#include <QLineEdit>
#include <QObject>
#include <QDebug>

#include "core/Widget/Widget.h"
#include "engineUtils.hpp"
#include "components/Components.hpp"

class SInput : public QLineEdit , public CoreWidget {
    Q_OBJECT

  public:
    SET_YOGA_COMP_Q_PROPERTIES

    using QLineEdit::QLineEdit;
    SInput(QWidget *parentWidget = nullptr);

    void connectSignal();
};