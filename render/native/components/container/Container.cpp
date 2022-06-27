#include "Container.h"

SMainWindow* SMainWindow::getInstance () {
  if (SMainWindowInstance == nullptr) {
    SMainWindowInstance = new SMainWindow();
  }
  return SMainWindowInstance;
}