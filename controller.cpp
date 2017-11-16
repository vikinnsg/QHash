// THIS FILE IS PART OF QHASH PROJECT
// controller.cpp - The part of the application

// THIS PROGRAM IS FREE SOFTWARE, GPL3.0 , IS LICENSED UNDER GPL3.0
// YOU SHOULD HAVE RECEIVED A COPY OF WTFPL LICENSE, IF NOT, BALABALA

// Copyright (c) 2017 vikinn

#include "controller.h"
#include "worker.h"
#include <QThread>
#include <QTimer>
//#include <QDebug>

Controller::Controller(QString filename, QMap<QString, bool> hashtargets, QObject *parent):
    QObject(parent),
    File(new QFile(filename,this)),
    HashTargets(hashtargets),
    Result(QString("<span style='color:red;'>").append(filename).append("</span>"))
{

}

QFile *Controller::getFile() const
{
    return File;
}

void Controller::sendResult()
{
    emit resultReady(Result);
}

void Controller::sendHashOver(QString hash, QString result)
{
//    qDebug()<<"Controller:emit hashOver(hash,result)"<<hash<<result;
    emit hashOver(hash,result);
    Result.append("<p style='color:green;padding:0;margin:0;'>").append(result).append("</p>");
//    qDebug()<<"Controller:Result"<<Result;
}

void Controller::opreator()
{
    if (!File->open(QIODevice::ReadOnly)){
        return;
    }

    QMapIterator<QString,bool> i(HashTargets);
    QThread *t=nullptr;

    while (i.hasNext()){
        i.next();
        if(i.value()){
            t=new QThread(this);
            ThreadsMap.insert(i.key(),t);
            Worker *w=new Worker(File,i.key());
            w->moveToThread(t);

            QObject::connect(w,&Worker::resultReady,this,&Controller::sendHashOver);
            QObject::connect(w,&Worker::resultReady,t,&QThread::quit);
//            QObject::connect(t,&QThread::started,w,&Worker::doWorke);

            QObject::connect(t,&QThread::started,[=](){
//                qDebug()<<"Comtroller:QThread started"<<File<<i.key();
                emit startHash(i.key());
                QTimer::singleShot(0,w,&Worker::doWorke);
            });
        }
    }

    QMapIterator<QString,QThread *> i1(ThreadsMap);
    while(i1.hasNext()){
        i1.next();
        if(i1.hasNext()){
//            qDebug()<<"connect"<<i1.key()<<"to"<<i1.peekNext().key();
            QObject::connect(i1.value(),&QThread::finished,[=](){i1.peekNext().value()->start();});
        }else{
            QObject::connect(i1.value(),&QThread::finished,[=](){

//                qDebug()<<"QThread::finished";
                File->close();
                QTimer::singleShot(200,this,&sendResult);
//                qDebug()<<"Controller:emit resultReady(Result)"<<Result;
            });
        }
    }
    ThreadsMap.first()->start();
}
