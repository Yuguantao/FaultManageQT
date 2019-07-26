#ifndef DIALOGEXPORT_H
#define DIALOGEXPORT_H

#include <QDialog>

namespace Ui {
class DialogExport;
}

class DialogExport : public QDialog
{
    Q_OBJECT

public:
    explicit DialogExport(QWidget *parent = 0);
    ~DialogExport();

    QString ipValue;

private slots:

    void on_ExputMana_clicked();

    void on_ExputFault_clicked();

public slots:

    void getIpValue(QString index);

private:
    Ui::DialogExport *ui;
};

#endif // DIALOGEXPORT_H
