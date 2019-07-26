#ifndef STUINFOMANAGE_H
#define STUINFOMANAGE_H

#include <QMainWindow>
#include "manage.h"
#include <QString>
#include <QtWidgets>
#include <QTimer>

namespace Ui {
class StuInfoManage;
}

class StuInfoManage : public QMainWindow
{
    Q_OBJECT

public:
    explicit StuInfoManage(QWidget *parent = 0);
    ~StuInfoManage();

    void showdata();

    //void tabletimeslot();


private slots:
    void on_addfinfo_clicked();

    void on_selectinfo_clicked();

    void on_exit_clicked();
public slots:
    void tabletimeslot();

private:
    Ui::StuInfoManage *ui;
    Manage *Sparent;
    QTimer *tabletime;
    int t;
};

#endif // STUINFOMANAGE_H
