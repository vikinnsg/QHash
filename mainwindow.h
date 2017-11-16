// THIS FILE IS PART OF QHASH PROJECT
// mainwindow.cpp- The mainwindow of the application
//
// THIS PROGRAM IS FREE SOFTWARE, GPL3.0 , IS LICENSED UNDER GPL3.0
// YOU SHOULD HAVE RECEIVED A COPY OF WTFPL LICENSE, IF NOT, BALABALA
//
// Copyright (c) 2017 vikinn

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QCryptographicHash>

class Dialog;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void getResult(QStringList result);

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);

private slots:
    void on_actionOpen_triggered();

    void on_actionHash_triggered();

    void on_search_clicked();

    void on_actionSave_triggered();

    void on_actionAbout_triggered();

    void on_hash_clicked();

private:
    Ui::MainWindow *ui;
    QStringList FileList;
    QMap<QString,bool> HashTargets;
    Dialog *h;

};

#endif // MAINWINDOW_H
