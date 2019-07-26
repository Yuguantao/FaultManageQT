#include "selectinfo.h"
#include "ui_selectinfo.h"
#include "mysql.h"
#include <QTableView>

selectinfo::selectinfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::selectinfo)
{
    Sparent=(StuInfoManage*) parent;

    ui->setupUi(this);
}

selectinfo::~selectinfo()
{
    delete ui;
}

void selectinfo::on_pushButton_clicked()
{
    my_stu tran;

    tran.man_sys = ui->man_sys->text();
    tran.man_model = ui->man_model->text();
    tran.man_num = ui->man_num->text();

    QProgressDialog dialog(tr("正在查询"),tr("取消"), 0, 30000, this);
    dialog.setWindowTitle(tr("进度"));
    dialog.setWindowModality(Qt::WindowModal);
    dialog.show();
    for(int k = 0; k < 30000; k++)
    {
        dialog.setValue(k);
        QCoreApplication::processEvents();
        if(dialog.wasCanceled())
        {
            break;
        }
    }
    dialog.setValue(30000);

    systemslot(tran.man_sys,tran.man_model,tran.man_num);
    QMessageBox::information(this, tr("消息"), tr("查询成功!"), QMessageBox::Ok);
    return;
}

void selectinfo::on_exit_clicked()
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

void selectinfo::systemslot(QString mansys,QString manmodel,QString mannum)
{
    ui->information_tableWidget->clearContents();
    //ui->information_tableWidget->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

    query=new QSqlQuery;

    QString str=QString("select * from faultdbmanage_managetable where man_sys='%1' and man_model = '%2' and man_num = '%3'").arg(mansys).arg(manmodel).arg(mannum);

    query->exec(str);

    int t=0;

    while(query->next())
    {
        ui->information_tableWidget->insertRow(t);
        ui->information_tableWidget->setItem(t,0,new QTableWidgetItem(query->value(2).toString()));
        ui->information_tableWidget->setItem(t,1,new QTableWidgetItem(query->value(3).toString()));
        ui->information_tableWidget->setItem(t,2,new QTableWidgetItem(query->value(4).toString()));
        ui->information_tableWidget->setItem(t,3,new QTableWidgetItem(query->value(5).toString()));
        ui->information_tableWidget->setItem(t,4,new QTableWidgetItem(query->value(6).toString()));
        ui->information_tableWidget->setItem(t,5,new QTableWidgetItem(query->value(8).toString()));
        ui->information_tableWidget->setItem(t,6,new QTableWidgetItem(query->value(10).toString()));
        ui->information_tableWidget->setItem(t,7,new QTableWidgetItem(query->value(11).toString()));
        ui->information_tableWidget->setItem(t,8,new QTableWidgetItem(query->value(12).toString()));
        ui->information_tableWidget->setItem(t,9,new QTableWidgetItem(query->value(13).toString()));
        ui->information_tableWidget->setItem(t,10,new QTableWidgetItem(query->value(9).toString()));
        ui->information_tableWidget->setItem(t,11,new QTableWidgetItem(query->value(15).toString()));
        t++;
    }
}
