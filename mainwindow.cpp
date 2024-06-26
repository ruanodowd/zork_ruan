#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <string>
#include <QScrollBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    counter = 0;
    changeLogText(zorkUL.getLastOutput());
}
//destructor
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeText()
{
    counter = counter + 1;
    QString s = QString::number(counter);
    ui->label20->setText(s);
}

void MainWindow::changeLogText(string fullLog){
    QString s = QString::fromStdString(fullLog);
    ui->log->setText(s);
}

void MainWindow::on_lineEdit_returnPressed()
{
    bool finished = zorkUL.update(ui->lineEdit->text().toStdString());
    changeText();
    changeLogText(zorkUL.getLastOutput());
    QScrollBar *scrollBar = ui->log->verticalScrollBar();
    scrollBar->setValue(scrollBar->maximum());




    if (finished)
        QCoreApplication::quit();

    ui->lineEdit->clear();
}

