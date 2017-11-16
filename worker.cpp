// THIS FILE IS PART OF QHASH PROJECT
// worker.cpp- The part of the application

// THIS PROGRAM IS FREE SOFTWARE, GPL3.0 , IS LICENSED UNDER GPL3.0
// YOU SHOULD HAVE RECEIVED A COPY OF WTFPL LICENSE, IF NOT, BALABALA

// Copyright (c) 2017 vikinn

#include "worker.h"
//#include <QDebug>
#include <QCryptographicHash>
#include <QFile>
#include <QMetaEnum>
#include <QThread>

Worker::Worker(QFile *file, QString hash, QObject *parent):
    QObject(parent),
    File(file),
    Result("")
{
    //字符串转枚举值
    QMetaEnum metaEnum = QMetaEnum::fromType<QCryptographicHash::Algorithm>();
    Type=(QCryptographicHash::Algorithm)metaEnum.keyToValue(hash.toUtf8().data());
//    qDebug()<<Type;

}

void Worker::doWorke()
{
//    qDebug()<<"dowork";
    File->seek(0);

    QCryptographicHash Hash(Type);
    Hash.addData(File);
    QMetaEnum metaEnum = QMetaEnum::fromType<QCryptographicHash::Algorithm>();
    QString hash(metaEnum.valueToKey(Type));

    Result.append(hash.toUpper()).append(": ").append(Hash.result().toHex().toUpper());

//    qDebug()<<"Worker:emit resultReady(hash,Result)"<<hash<<Result;
    emit resultReady(hash,Result);
    this->thread()->quit();
}

