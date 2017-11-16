// THIS FILE IS PART OF QHASH PROJECT
// worker.h - The part of the application
//
// THIS PROGRAM IS FREE SOFTWARE, GPL3.0 , IS LICENSED UNDER GPL3.0
// YOU SHOULD HAVE RECEIVED A COPY OF WTFPL LICENSE, IF NOT, BALABALA
//
// Copyright (c) 2017 vikinn

#ifndef WORKER_H
#define WORKER_H

#include <QCryptographicHash>
#include <QFile>
#include <QObject>

class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(QFile *file, QString hash, QObject *parent = nullptr);
signals:
    void resultReady(QString hash,QString result);

public slots:
    void doWorke();

private:
    QFile *File;
    QString Result;
    QCryptographicHash::Algorithm Type;
};

#endif // WORKER_H
