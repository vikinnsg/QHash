// THIS FILE IS PART OF QHASH PROJECT
// dialog.h- The part of the application
//
// THIS PROGRAM IS FREE SOFTWARE, GPL3.0 , IS LICENSED UNDER GPL3.0
// YOU SHOULD HAVE RECEIVED A COPY OF WTFPL LICENSE, IF NOT, BALABALA
//
// Copyright (c) 2017 vikinn

#ifndef DIALOG_H
#define DIALOG_H



#include <QDialog>
#include <QMap>

class Controller;

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QStringList filelist, QMap<QString,bool> hashtargets, QWidget *parent = 0);
    ~Dialog();
public slots:
    void getResult(QString result);
signals:
    void resultReady(QStringList Result);

private:
    Ui::Dialog *ui;
    QStringList FileList;
    QMap<QString,bool> HashTargets;
    QString HashResult;
    Controller *controller;
    QStringList Result;
};

#endif // DIALOG_H
