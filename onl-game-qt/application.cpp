#include "application.h"


TApplication::TApplication(int argc, char *argv[])
            : QCoreApplication(argc,argv)
{
    TCommParams pars = { QHostAddress("127.0.0.1"), 10000,
                         QHostAddress("127.0.0.1"), 10001};
    comm = new TCommunicator(pars, this);

    connect(comm,SIGNAL(recieved(QByteArray)),this,SLOT(recieve(QByteArray)));
}

void hexByteArray(QByteArray msg){
    QString out = QString(msg);
    qInfo() << out;
}

void TApplication::recieve(QByteArray msg) {
    qDebug("sended");
    QString out = QString(msg);

    int size = out.split(" ")[0].toInt();
    out = out.remove(0, out.indexOf(' ') + 1);

    int **second_player = new int *[size];
    for (int i = 0; i < size; i++) {
        second_player[i] = new int [size];
        for (int j = 0; j < size; j++){
            **second_player = out.split(" ")[0].toInt();
            out = out.remove(0, out.indexOf(' ') + 1);
        }
    }

    Game.SetPlayerValuesFromOther(second_player);

    /*matrix = new Matrix(size);

    switch(sep) {
    case DETERMINANT:{
        number de = matrix->matrix_determinant();
        QByteArray out_msg;
        out_msg.append(QString::number(DETERMINANT).toLocal8Bit());
        out_msg.append(' ');
        QString st;
        st << de;
        out_msg.append(st.toLocal8Bit());
        comm->send(out_msg);
        break;
    }

    case RANK: {
        int ra = matrix->matrix_rg();
        QByteArray out_msg;
        out_msg.append(QString::number(RANK).toLocal8Bit());
        out_msg.append(' ');
        out_msg.append(QString::number(ra).toLocal8Bit());
        comm->send(out_msg);
        break;
    }

    case MATRIX_TRANSPOSE:{
        matrix->matrix_transpose();
        QByteArray out_msg;
        out_msg.append(QString::number(MATRIX_TRANSPOSE).toLocal8Bit());
        out_msg.append(' ');

        QString str;
        str << *matrix;
        str.chop(1);
        out_msg.append(str.toLocal8Bit());
        comm->send(out_msg);
        break;
        }

        default: {
            comm->send("no info");
        }
    }*/
}
