#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ZorkUL.h"
#include "Command.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void changeLogText(string);
    ~MainWindow();

signals:
    void textUpdated(int counter);
private slots:
    void on_lineEdit_returnPressed();
    void changeText();

private:
    Ui::MainWindow *ui;
    ZorkUL zorkUL;
    int counter;
};
#endif // MAINWINDOW_H
