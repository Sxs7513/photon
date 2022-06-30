#pragma once

#include <QTextEdit>
#include <QObject>
#include <QDebug>

#include "core/Widget/Widget.h"
#include "engineUtils.hpp"
#include "components/Components.hpp"

class STextarea : public QTextEdit , public CoreWidget {
    Q_OBJECT

  public:
    SET_YOGA_COMP_Q_PROPERTIES

    using QTextEdit::QTextEdit;
    STextarea(QWidget *parentWidget = nullptr);

    void connectSignal();
};