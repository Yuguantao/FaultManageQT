#include "fault.h"
#include "ui_fault.h"
#include "manage.h"
#include <QSqlTableModel>
#include <QTableView>
#include <QInputDialog>
#include "qprogressdialog.h"
#include "addfault.h"
#include "selectfau.h"
#include "mysql.h"
#include <QTableWidgetItem>
#include <QTableWidget>


fault::fault(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::fault)
{
    Sparent = (Manage*) parent;
    ui->setupUi(this);

    faultTable();
}

fault::~fault()
{
    delete ui;
}

void fault::on_addfinfo_clicked()
{
    this->hide();
    addFault *AI=new addFault(this);
    AI->show();
}

void fault::on_selectinfo_clicked()
{
    this->hide();
    selectFau *AI=new selectFau(this);
    AI->show();
}

void fault::on_exit_clicked()
{
    this->close();
    QProgressDialog dialog(tr("正在返回主界面"),tr("取消"), 0, 3000, this);
    dialog.setWindowTitle(tr("进度"));
    dialog.setWindowModality(Qt::WindowModal);
    dialog.show();
    for(int k = 0; k < 3000; k++)
    {
        dialog.setValue(k);
        QCoreApplication::processEvents();
        if(dialog.wasCanceled())
        {
            break;
        }
    }
    dialog.setValue(3000);
    Sparent->show();
}

void fault::faultTable()
{
    ui->information_tableWidget->clearContents();

    QSqlQuery query(MySql::getDb());

    query.exec("select * from faultdbmanage_faulttable");
    int t=0;

    while(query.next())
    {
        ui->information_tableWidget->insertRow(t);
        ui->information_tableWidget->setItem(t,0,new QTableWidgetItem(query.value(3).toString()));
        ui->information_tableWidget->setItem(t,1,new QTableWidgetItem(query.value(4).toString()));
        ui->information_tableWidget->setItem(t,2,new QTableWidgetItem(query.value(5).toString()));
        ui->information_tableWidget->setItem(t,3,new QTableWidgetItem(query.value(6).toString()));
        ui->information_tableWidget->setItem(t,4,new QTableWidgetItem(query.value(7).toString()));
        ui->information_tableWidget->setItem(t,5,new QTableWidgetItem(query.value(8).toString()));
        ui->information_tableWidget->setItem(t,6,new QTableWidgetItem(query.value(9).toString()));
        ui->information_tableWidget->setItem(t,7,new QTableWidgetItem(query.value(10).toString()));
        ui->information_tableWidget->setItem(t,8,new QTableWidgetItem(query.value(11).toString()));
        ui->information_tableWidget->setItem(t,9,new QTableWidgetItem(query.value(13).toString()));
        ui->information_tableWidget->setItem(t,10,new QTableWidgetItem(query.value(12).toString()));
        ui->information_tableWidget->setItem(t,11,new QTableWidgetItem(query.value(15).toString()));
        t++;
    }
}
