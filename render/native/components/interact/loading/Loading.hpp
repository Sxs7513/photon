#pragma once
#include <QWidget>
#include <QTimer>
#include <QFrame>
#include <QMovie>
#include <QLabel>
#include <QDebug>

#include <uv.h>

#include "components/container/Container.h"
#include "components/mask/Mask.hpp"
#include "engineUtils.hpp"

extern "C" {
    #include <jsapi.h>
    #include <uv.h>
}

class SLoading : public QWidget
{
    Q_OBJECT
public:
    using QWidget::QWidget;
    SLoading(QWidget *parentWidget = nullptr);
    ~SLoading();

    static void getIntace();
    static void showLoading();
    static void hideLoading();
    static void setText (std::string text);

private:
    std::string text;
    QLabel* label;
    QMovie* movie;
    QFrame* layout;
    SMask* mask;
};

static SLoading* LoadingInstance = nullptr;
