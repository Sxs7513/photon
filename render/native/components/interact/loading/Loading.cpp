#include "Loading.hpp"

void SLoading::getIntace () {
    if (LoadingInstance == nullptr) {
        LoadingInstance = new SLoading(SMainWindow::getInstance());
        LoadingInstance->setFixedSize(150, 150);
        LoadingInstance->layout = new QFrame(LoadingInstance);
        LoadingInstance->layout->setStyleSheet("background-color:rgba(0,0,0,0.6);border-radius:10px;");

        LoadingInstance->label = new QLabel(LoadingInstance->layout);
        LoadingInstance->label->setGeometry(50, 50, 50, 50);

        char* buf = (char*)malloc(PATH_MAX);
        GetEngineAssetPath(buf, "loading.gif"); 
        LoadingInstance->movie = new QMovie(buf);
        free(buf);
        LoadingInstance->label->setScaledContents(true);
        LoadingInstance->label->setMovie(LoadingInstance->movie);
        LoadingInstance->movie->start();

        LoadingInstance->mask = new SMask(SMainWindow::getInstance());
        LoadingInstance->mask->raise();
        LoadingInstance->raise();
    }
};

void SLoading::showLoading() {
    SLoading::getIntace();
    if (LoadingInstance != nullptr) {
        LoadingInstance->move((SMainWindow::getInstance()->width() - LoadingInstance->width()) / 2, (SMainWindow::getInstance()->height() - LoadingInstance->height()) / 2);
        LoadingInstance->layout->setGeometry(0, 0, 150, 150);
        LoadingInstance->show();
        LoadingInstance->mask->show();
    }
};

void SLoading::hideLoading() {
    if (LoadingInstance != nullptr) {
        qWarning() << "hide loading";
        LoadingInstance->hide();
        LoadingInstance->mask->hide();
    }
};

SLoading::SLoading(QWidget *parentWidget): QWidget(parentWidget) {};

SLoading::~SLoading() {
    // if (LoadingInstance != nullptr) {
    //     delete LoadingInstance->layout;
    // }
};

void SLoading::setText (std::string text) {
    SLoading::getIntace();
    if (LoadingInstance != nullptr) {
        LoadingInstance->text = text;
    }
};