#pragma once
#include <QMainWindow>

#include "core/Widget/Widget.h"

class SMainWindow : public QMainWindow, public CoreWidget {
  Q_OBJECT

 public:
  SET_YOGA_COMP_Q_PROPERTIES
  using QMainWindow::QMainWindow;

  static SMainWindow* getInstance();

};

static SMainWindow* SMainWindowInstance = nullptr;