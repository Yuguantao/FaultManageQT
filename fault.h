#ifndef FAULT_H
#define FAULT_H

#include <QMainWindow>
#include "manage.h"
#include <QSqlQuery>

namespace Ui {
class fault;
}

class fault : public QMainWindow
{
    Q_OBJECT

public:
    explicit fault(QWidget *parent = 0);
    ~fault();

private slots:
    void on_addfinfo_clicked();

    void on_selectinfo_clicked();

    void on_exit_clicked();

public slots:
    void faultTable();

private:
    Ui::fault *ui;
    Manage *Sparent;
};

#endif // FAULT_H
