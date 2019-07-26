#include "mainwindow.h"
#include <QApplication>
#include "mysql.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MySql::initsql();
    MainWindow* w = MainWindow::getIntance();
    w->setWindowTitle("故障数据库管理系统 v1.0");
    w->show();

    return a.exec();
}
