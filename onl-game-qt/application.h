#ifndef TAPPLICATION_H
#define TAPPLICATION_H

#include <QObject>
#include <QCoreApplication>
#include "widget.h"
#include "field.h"

#include "communicator.h"

class TApplication : public QCoreApplication
{
    Q_OBJECT
    Field Game;
    int** second_player = nullptr;

    TCommunicator *comm;

public:

    TApplication(int, char**);

signals:

public slots:

    void recieve(QByteArray);
};

#endif // TAPPLICATION_H
