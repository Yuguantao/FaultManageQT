#include "stuinfomanage.h"
#include "changestuinfo.h"
#include "manage.h"
#include "addinfo.h"
#include "selectinfo.h"
#include "ui_stuinfomanage.h"
#include <QSqlTableModel>
#include <QTableView>
#include <QInputDialog>
#include "mysql.h"
#include <QTableWidgetItem>

enum studentInfoIndex
{

    faultdbmanage_managetable_man_sys = 2,
    faultdbmanage_managetable_man_model = 3,
    faultdbmanage_managetable_man_num = 4,
    faultdbmanage_managetable_man_impTime = 5,
    faultdbmanage_managetable_man_porpuse = 6,
    faultdbmanage_managetable_man_place = 8,
    faultdbmanage_managetable_man_department = 10,
    faultdbmanage_managetable_man_persion = 11,
    faultdbmanage_managetable_man_mfrs = 12,
    faultdbmanage_managetable_man_mfrspersion = 13,
    faultdbmanage_managetable_man_enclosure = 9,
    faultdbmanage_managetable_man_remarks = 15
};

StuInfoManage::StuInfoManage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StuInfoManage)
{
    Sparent =(Manage*) parent;
    ui->setupUi(this);

    tabletimeslot();
}

StuInfoManage::~StuInfoManage()
{
    delete ui;
}

void StuInfoManage::on_addfinfo_clicked()
{
    this->hide();
    AddInfo *AI=new AddInfo(this);

    AI->show();
}

void StuInfoManage::on_selectinfo_clicked()
{
    this->hide();
    selectinfo *AI=new selectinfo(this);
    AI->show();
}



void StuInfoManage::showdata()
{
    QSqlTableModel *model=new QSqlTableModel();
    model->setTable("faultdbmanage_managetable");
    //model->setSort(faultdbmanage_managetable_man_impTime,Qt::AscendingOrder);
    model->setHeaderData(faultdbmanage_managetable_man_sys,Qt::Horizontal,"系统");
    model->setHeaderData(faultdbmanage_managetable_man_model,Qt::Horizontal,"型号");
    model->setHeaderData(faultdbmanage_managetable_man_num,Qt::Horizontal,"编号");
    model->setHeaderData(faultdbmanage_managetable_man_impTime,Qt::Horizontal,"进场日期");
    model->setHeaderData(faultdbmanage_managetable_man_porpuse,Qt::Horizontal,"功能用途");
    model->setHeaderData(faultdbmanage_managetable_man_place,Qt::Horizontal,"存放地点");
    model->setHeaderData(faultdbmanage_managetable_man_department,Qt::Horizontal,"责任部门");
    model->setHeaderData(faultdbmanage_managetable_man_persion,Qt::Horizontal,"责任人");
    model->setHeaderData(faultdbmanage_managetable_man_mfrs,Qt::Horizontal,"生产厂家");
    model->setHeaderData(faultdbmanage_managetable_man_mfrspersion,Qt::Horizontal,"厂家联系人");
    model->setHeaderData(faultdbmanage_managetable_man_enclosure,Qt::Horizontal,"备附件说明");
    model->setHeaderData(faultdbmanage_managetable_man_remarks,Qt::Horizontal,"备注");

    model->select();

    QTableView *view=new QTableView;
    view->setModel(model);
    view->setSelectionMode(QAbstractItemView::SingleSelection);
    view->setSelectionBehavior(QAbstractItemView::SelectRows);
    view->setColumnHidden(faultdbmanage_managetable_man_impTime, true);
    view->resizeColumnsToContents();
    view->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QHeaderView *header=view->horizontalHeader();
    header->setStretchLastSection(true);
    view->resize(600, 450);

    view->show();
}


void StuInfoManage::on_exit_clicked()
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

void StuInfoManage::tabletimeslot()
{
    ui->information_tableWidget->clearContents();

    QSqlQuery query(MySql::getDb());

    query.exec("select * from faultdbmanage_managetable");
    int t=0;

    while(query.next())
    {
        ui->information_tableWidget->insertRow(t);
        ui->information_tableWidget->setItem(t,0,new QTableWidgetItem(query.value(2).toString()));
        ui->information_tableWidget->setItem(t,1,new QTableWidgetItem(query.value(3).toString()));
        ui->information_tableWidget->setItem(t,2,new QTableWidgetItem(query.value(4).toString()));
        ui->information_tableWidget->setItem(t,3,new QTableWidgetItem(query.value(5).toString()));
        ui->information_tableWidget->setItem(t,4,new QTableWidgetItem(query.value(6).toString()));
        ui->information_tableWidget->setItem(t,5,new QTableWidgetItem(query.value(8).toString()));
        ui->information_tableWidget->setItem(t,6,new QTableWidgetItem(query.value(10).toString()));
        ui->information_tableWidget->setItem(t,7,new QTableWidgetItem(query.value(11).toString()));
        ui->information_tableWidget->setItem(t,8,new QTableWidgetItem(query.value(12).toString()));
        ui->information_tableWidget->setItem(t,9,new QTableWidgetItem(query.value(13).toString()));
        ui->information_tableWidget->setItem(t,10,new QTableWidgetItem(query.value(9).toString()));
        ui->information_tableWidget->setItem(t,11,new QTableWidgetItem(query.value(15).toString()));
        t++;
    }
}
