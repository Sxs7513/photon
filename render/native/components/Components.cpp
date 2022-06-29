#include "Components.hpp"

void QStringToChar(QString source, char** dst) {
    QByteArray ba = source.toLocal8Bit();
    *dst = ba.data();
};