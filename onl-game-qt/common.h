#ifndef COMMON_H
#define COMMON_H

#include <QString>

enum messages
{
    row = 1,
    collumn = 2,
    DISCONNECT
};

extern const QChar separator;
QString& operator<< (QString&,const QString&);

#endif // COMMON_H
