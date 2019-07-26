#ifndef ADDINFO_H
#define ADDINFO_H

#include <QMainWindow>
#include <QPushButton>
#include <QMessageBox>
#include <QProgressDialog>
#include "stuinfomanage.h"

namespace Ui {
class AddInfo;
}

class AddInfo : public QMainWindow
{
    Q_OBJECT

public:
    explicit AddInfo(QWidget *parent = 0);
    ~AddInfo();

signals:
    void upDate();

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::AddInfo *ui;
    StuInfoManage *Sparent;
};


typedef struct stuInfo
{    
    QString uuid;
    QString man_sys;
    QString man_model;
    QString man_num;
    QString man_impTime;
    QString man_porpuse;
    QString man_place;
    QString man_enclosure;
    QString man_department;
    QString man_persion;
    QString man_mfrspersion;
    QString man_remarks;
    QString man_mfrs;

}my_stu;

#endif // ADDINFO_H
