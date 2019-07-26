#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

    QString ipValue;

private slots:

    void on_inputMana_clicked();

    void on_inputFault_clicked();

public slots:

    void getIpValue(QString index);

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
