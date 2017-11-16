// THIS FILE IS PART OF QHASH PROJECT
// controller.h - The part of the application
//
// THIS PROGRAM IS FREE SOFTWARE, GPL3.0 , IS LICENSED UNDER GPL3.0
// YOU SHOULD HAVE RECEIVED A COPY OF WTFPL LICENSE, IF NOT, BALABALA
//
// Copyright (c) 2017 vikinn

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QFile>
#include <QMap>
#include <QObject>
//#include <QCryptographicHash>

class Controller:public QObject
{
    Q_OBJECT
public:
    Controller(QString filename, QMap<QString,bool> hashtargets, QObject *parent);
    QFile* getFile() const;
    void sendResult();
private slots:
    void sendHashOver(QString hash,QString result);

signals:
    void startHash(QString hash);
    void resultReady(QString result);
    void hashOver(QString hash,QString result);

public slots:
    void opreator();

private:
    QFile *File;
    QMap<QString,bool> HashTargets;
    QMap<QString,QThread *> ThreadsMap;
    QString Result;

};

#endif // CONTROLLER_H
