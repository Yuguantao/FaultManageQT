#ifndef MANAGE_H
#define MANAGE_H

#include <QMainWindow>
#include <QMessageBox>
#include <QProgressDialog>

namespace Ui {
class Manage;
}

class Manage : public QMainWindow
{
    Q_OBJECT

public:
    explicit Manage(QWidget *parent = 0);
    ~Manage();

    QString IpValue;

private slots:
    void on_stuInfo_clicked();
    
    void on_liceInfo_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_connectBtn_clicked();

private:
    Ui::Manage *ui;
};

#endif // MANAGE_H
