#ifndef SELECTINFO_H
#define SELECTINFO_H

#include <QMainWindow>
#include <QPushButton>
#include <QMessageBox>
#include <QProgressDialog>
#include "stuinfomanage.h"
#include <QSqlQuery>
#include <QtWidgets>
#include <QTimer>

namespace Ui {
class selectinfo;
}

class selectinfo : public QDialog
{
    Q_OBJECT

public:
    explicit selectinfo(QWidget *parent = 0);
    ~selectinfo();

private slots:

    void on_pushButton_clicked();

    void on_exit_clicked();

    void systemslot(QString mansys, QString manmodel, QString mannum);

private:
    Ui::selectinfo *ui;
    StuInfoManage *Sparent;
    QSqlQuery *query;
    int t;
};

#endif // SELECTINFO_H
