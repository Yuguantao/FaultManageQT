#ifndef SELECTFAU_H
#define SELECTFAU_H

#include <QMainWindow>
#include "fault.h"

namespace Ui {
class selectFau;
}

class selectFau : public QMainWindow
{
    Q_OBJECT

public:
    explicit selectFau(QWidget *parent = 0);
    ~selectFau();

private slots:
    void on_exit_clicked();

    void on_pushButton_clicked();

public slots:
    void faultslot(QString mansys, QString manmodel, QString mannum);

private:
    Ui::selectFau *ui;
    fault*Sparent;
    QSqlQuery*query;
};

#endif // SELECTFAU_H
