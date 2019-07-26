#ifndef ADDFAULT_H
#define ADDFAULT_H

#include <QMainWindow>
#include <QPushButton>
#include <QMessageBox>
#include <QProgressDialog>
#include "fault.h"

namespace Ui {
class addFault;
}

class addFault : public QMainWindow
{
    Q_OBJECT

public:
    explicit addFault(QWidget *parent = 0);
    ~addFault();

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

    void on_pushButton_clicked();

public slots:
    void getSystem();

private:
    Ui::addFault *ui;
    fault*Sparent;
    QStringList stringSys;
    QStringList stringModal;
    QStringList stringNum;
    QString fau_manInfo1;
    QSqlQuery *query;

};

typedef struct faultInfo
{
    QString uuid;
    QString fau_manInfo;
    QString fau_time;
    QString fau_phen;
    QString fau_desc;
    QString fau_type;
    QString fau_num;
    QString fau_reason;
    QString fau_effect;
    QString fau_check;
    QString fau_measure;
    QString fau_advise;
    QString fau_peopleInfo;
    QString fau_remarks;


}my_fau;

#endif // ADDFAULT_H
