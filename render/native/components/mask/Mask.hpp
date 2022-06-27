#pragma once
#include <QWidget>
#include <QString>
#include <QDebug>

class SMask : public QWidget {
    using QWidget::QWidget;

  public:
    SMask(QWidget *parentWidget = nullptr);
    void setParent(QWidget* parent);
    void showEvent(QShowEvent* event);

    const char* styleSheet = nullptr;
};