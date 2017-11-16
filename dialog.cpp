// THIS FILE IS PART OF QHASH PROJECT
// dialog.cpp- The part of the application

// THIS PROGRAM IS FREE SOFTWARE, GPL3.0 , IS LICENSED UNDER GPL3.0
// YOU SHOULD HAVE RECEIVED A COPY OF WTFPL LICENSE, IF NOT, BALABALA

// Copyright (c) 2017 vikinn

#include "dialog.h"
#include "ui_dialog.h"
#include "controller.h"
#include <QGroupBox>
#include <QVBoxLayout>
#include <QProgressBar>
#include <QMapIterator>
//#include <QDebug>
#include <QTimer>

Dialog::Dialog(QStringList filelist, QMap<QString, bool> hashtargets, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog),
    FileList(filelist),
    HashTargets(hashtargets),
    HashResult("")
{
//    qDebug()<<HashTargets;
    ui->setupUi(this);
    //temp varable
    QString filename;
    Controller *c=nullptr;
    QProgressBar *progressBar=nullptr;

    foreach (filename,FileList)
    {
        c=new Controller(filename,HashTargets,this);

        QGroupBox *groupBox = new QGroupBox(this);
        groupBox->setTitle(filename);

        ui->verticalLayout_2->insertWidget(0,groupBox);

        QVBoxLayout *verticalLayout = new QVBoxLayout(groupBox);

        QMapIterator<QString,bool> i(HashTargets);

        while(i.hasNext())
        {
            i.next();
            QString s=i.key();
            progressBar = new QProgressBar(groupBox);
            progressBar->setObjectName(filename);
            progressBar->setFormat(s.toUpper().append(": [%p%]"));
            progressBar->setValue(0);
            verticalLayout->addWidget(progressBar);

            QTimer *timer=new QTimer(this);
            timer->setInterval(100);
//            timer->setObjectName("test");

//            qDebug()<<"new timer id="<<timer->timerId();
//            qDebug()<<"new timer objectname="<<timer->objectName();


            //开启定时器读取进度
            connect(c,&Controller::startHash,[=](QString hash){
//                qDebug()<<"dialog:receive startHash(hash)"<<hash;
                if(hash==i.key()){
                    connect(timer,&QTimer::timeout,[=]{
//                        qDebug()<<"timeout"<<timer->timerId();
                        if (progressBar->value()==100){
                            timer->stop();
                            return;
                        }
                        qreal pos=(qreal)(c->getFile()->pos());
                        qreal size=(qreal)(c->getFile()->size());

                        if(pos==0||size==0){
                            return;
                        }

                        int value=(int)(100*pos/size);
//                        qDebug()<<pos<<size<<value;
                        progressBar->setValue(value);

                    });
//                    qDebug()<<"timer start id="<<timer->timerId();
//                    qDebug()<<"timer start objectname="<<timer->objectName();
                    QTimer::singleShot(0,timer,static_cast<void(QTimer::*)()>(&QTimer::start));
                }
            });
            //完成进度关闭定时器
            connect(c,&Controller::hashOver,[=](QString hash,QString result){
//                qDebug()<<"dialog:receive hashover(hash,result),i.key()"<<hash<<result<<i.key();
                if(hash==i.key()){
//                    qDebug()<<"hashover==i.key()";
                    progressBar->setValue(100);
                    progressBar->setFormat(result.toUpper());
                    progressBar->setAlignment(Qt::AlignHCenter);
                }
            });
        }

        //收集控制器结果
        connect(c,&Controller::resultReady,this,&Dialog::getResult);

        //开启一个线程控制器
        QTimer::singleShot(0,c,&Controller::opreator);
    }
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::getResult(QString result)
{
    Result.append(result);
    if(Result.length()==FileList.length()){
//        qDebug()<<"Dialog:emit resultReady(Result)"<<Result;
        emit resultReady(Result);
        this->close();
//        QTimer::singleShot(0,[=](){this->destroy(true,true);});
    }
}
