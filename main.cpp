// THIS FILE IS PART OF QHASH PROJECT
// main.cpp- The entry of the application
//
// THIS PROGRAM IS FREE SOFTWARE, GPL3.0 , IS LICENSED UNDER GPL3.0
// YOU SHOULD HAVE RECEIVED A COPY OF WTFPL LICENSE, IF NOT, BALABALA
//
// Copyright (c) 2017 vikinn

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
