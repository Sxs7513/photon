#pragma once
#include <QLabel>
#include <QImage>
#include <QPixmap>
#include <QDebug>
#include <QByteArray>
#include <QBuffer>
#include <QIODevice>
#include <QMovie>
#include <QSharedPointer>

#include <stdlib.h>

#include "core/Widget/Widget.h"

#include "engineUtils.hpp"

#include "components/Components.hpp"

class SImage : public QLabel, public CoreWidget {
  Q_OBJECT

 public:
  SET_YOGA_COMP_Q_PROPERTIES
  using QLabel::QLabel;
  SImage(QWidget *parentWidget = nullptr);

};
