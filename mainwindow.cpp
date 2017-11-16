// THIS FILE IS PART OF QHASH PROJECT
// mainwindow.cpp- The mainwindow of the application

// THIS PROGRAM IS FREE SOFTWARE, GPL3.0 , IS LICENSED UNDER GPL3.0
// YOU SHOULD HAVE RECEIVED A COPY OF WTFPL LICENSE, IF NOT, BALABALA

// Copyright (c) 2017 vikinn

#include "dialog.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "worker.h"
#include <QFileDialog>
//#include <QDebug>
#include <QProgressBar>
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QLabel>
#include <QTimer>
#include <QThread>
#include <QMessageBox>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QTextCursor>
#include <QTextStream>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getResult(QStringList result)
{
    QString str;
    foreach(str,result){
        str.prepend("<div style=\" border: solid;padding: 10px;\" >");
        str.append("</div><p>\n</p>");
        ui->textEdit->append(str);
    }
    FileList.clear();
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if(event->mimeData()->hasUrls()){
        QCursor c=this->cursor();
//        c.setShape(Qt::ClosedHandCursor);
        this->setCursor(c);
        event->acceptProposedAction();
    }else{
        event->ignore();
    }
}

void MainWindow::dropEvent(QDropEvent *event)
{
    const QMimeData *mimeData=event->mimeData();
    if(mimeData->hasUrls()){
        QList<QUrl> urlList=mimeData->urls();
//        qDebug()<<urlList;
        QUrl u;
        QString s;
        FileList.clear();
        foreach(u,urlList){
            QString s=u.toLocalFile();
            if(!s.isEmpty()){
                FileList.append(s);
                this->ui->actionHash->triggered();
            }
        }
    }
}

void MainWindow::on_actionOpen_triggered()
{
    FileList=QFileDialog::getOpenFileNames();
}

void MainWindow::on_actionHash_triggered()
{
    QObjectList l=ui->groupBox->children();
    QObject *o=nullptr;
    foreach(o,l){//添加类型
        QString s(o->metaObject()->className());
        if(s.contains("QCheckBox")){//判断是否是checkbox
            QCheckBox* c=static_cast<QCheckBox *>(o);
            if(c->isChecked()){//更新选框状态
                HashTargets.insert(c->objectName(),true);
            }else{
                if(HashTargets.contains(c->objectName())){
                    HashTargets.insert(c->objectName(),true);
                }
            }
        }
    }
    if(!ui->textEdit->document()->isEmpty()){
        if(QMessageBox::question(this,"提示","是否清空上一次哈希运算的结果？")){
            ui->textEdit->clear();
        }
    }
    if (FileList.isEmpty()){
        FileList=QFileDialog::getOpenFileNames(this,"请选择文件，可以多选");
        if (FileList.isEmpty()){
            QMessageBox::information(this,"Tips","您没有选择文件",QMessageBox::Yes);
            return;
        }
    }
    if(HashTargets.isEmpty()){
        QObject *o=nullptr;
        foreach(o,l){
            QString s(o->metaObject()->className());
            if(s.contains("QCheckBox")){
                QCheckBox* c=static_cast<QCheckBox *>(o);
                c->setChecked(true);
                HashTargets.insert(c->objectName(),true);
            }
        }
    }
    h=new Dialog(FileList,HashTargets,this);
    h->setAttribute(Qt::WA_DeleteOnClose);
    connect(h,&Dialog::resultReady,this,&MainWindow::getResult);
    h->show();
}

void MainWindow::on_search_clicked()
{
//    ui->textEdit->setFocus();
    QTextCursor c =ui->textEdit->textCursor();
    c.movePosition(QTextCursor::Start);
    ui->textEdit->setTextCursor(c);
    QString str=ui->lineEdit->text();
    if (ui->textEdit->find(str/*,QTextDocument::FindBackward*/)){
        QPalette palette=ui->textEdit->palette();
        palette.setColor(QPalette::Highlight,palette.color(QPalette::Active,QPalette::Highlight));
        ui->textEdit->setPalette(palette);
    }else
    {
        QMessageBox::information(this,tr("注意"),tr("没有找到内容"),QMessageBox::Ok);
    }
}

void MainWindow::on_actionSave_triggered()
{
    if(ui->textEdit->document()->isEmpty()){
        QMessageBox::information(this,"Tips","结果为空");
        return;
    }else{
        QString path=QFileDialog::getSaveFileName(this,"选择保存位置");
        if (path.isEmpty()){
            QMessageBox::information(this,"Tips","您没有选择文件");
            return;
        }else{
            QFile file(path);
            if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
                QMessageBox::warning(this,"WARNING!","文件操作失败！");
                return;
            }else{
                QTextStream out(&file);
                out<<ui->textEdit->toPlainText();
            }
        }
    }

}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this,"about","开源哈希计算工具\n版本:1.0\n作者:VIKINN\n网站:http://www.vcvoo.com  \nGNU通用公共许可证\n版本3,2007年6月29日\nCopyright（C）2017 vikinn http://www.vcvoo.com\n每个人都可以复制和分发这个许可文件的逐字拷贝，但是不允许改变它。");
}

void MainWindow::on_hash_clicked()
{
    ui->actionHash->triggered();
}
