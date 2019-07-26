#include "addfault.h"
#include "ui_addfault.h"
#include "mysql.h"
#include <QStringList>

addFault::addFault(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::addFault)
{
    Sparent = (fault *)parent;
    ui->setupUi(this);
    getSystem();
}

addFault::~addFault()
{
    delete ui;
}

void addFault::on_buttonBox_clicked(QAbstractButton *button)
{
    if(ui->buttonBox->button(QDialogButtonBox::Ok) == button)
    {
        my_fau tran;

        QUuid id = QUuid::createUuid();
        tran.uuid = id.toString();
        tran.fau_manInfo = fau_manInfo1;
        tran.fau_phen = ui->fau_phen->text();
        tran.fau_desc = ui->fau_desc->text();
        tran.fau_type = ui->fau_type->text();
        tran.fau_time = ui->fau_time->date().toString("yyyy-MM-dd");
        tran.fau_num = ui->fau_num->text();
        tran.fau_reason = ui->fau_reason->text();
        tran.fau_effect = ui->fau_effect->text();
        tran.fau_check = ui->fau_check->text();
        tran.fau_measure = ui->fau_measure->text();
        tran.fau_advise = ui->fau_advise->text();
        tran.fau_peopleInfo = ui->fau_peopleInfo->text();
        tran.fau_remarks = ui->fau_remarks->toPlainText();

        QProgressDialog dialog(tr("正在添加"),tr("取消"), 0, 30000, this);
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

        MySql mysql;
        bool ret = mysql.addfau(&tran);
        if(ret == false)
        {
            QMessageBox::information(this, tr("消息"), tr("添加失败!"), QMessageBox::Ok);
            this->close();
            Sparent->show();
            return;
        }
        QMessageBox::information(this, tr("消息"), tr("添加成功!"), QMessageBox::Ok);
        Sparent->faultTable();
        this->close();
        Sparent->show();
        return;
    }
    else if(ui->buttonBox->button(QDialogButtonBox::Cancel) == button)
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
}

void addFault::getSystem()
{

    QSqlQuery query(MySql::getDb());

    query.exec("select * from faultdbmanage_managetable");

    while(query.next()){

        QString goodsSys = query.value(2).toString();
        stringSys.append(goodsSys);
        QString goodsModal = query.value(3).toString();
        stringModal.append(goodsModal);
        QString goodsNum = query.value(4).toString();
        stringNum.append(goodsNum);
    }

    ui->comboBoxSys->clear();
    ui->comboBoxSys->addItems(stringSys);
    ui->comboBoxModal->clear();
    ui->comboBoxModal->addItems(stringModal);
    ui->comboBoxNum->clear();
    ui->comboBoxNum->addItems(stringNum);
}

void addFault::on_pushButton_clicked()
{
    QString sysValue = ui->comboBoxSys->currentText();
    QString modalValue = ui->comboBoxModal->currentText();
    QString numValue = ui->comboBoxNum->currentText();

    query = new QSqlQuery;

    QString str=QString("select * from faultdbmanage_managetable where man_sys='%1' and man_model = '%2' and man_num = '%3'").arg(sysValue).arg(modalValue).arg(numValue);

    query->exec(str);

    if(query->next())
    {
        QMessageBox::information(this, tr("消息"), tr("选择成功!"), QMessageBox::Ok);
        fau_manInfo1 = query->value(0).toString();

    }else{
        QMessageBox::information(this, tr("消息"), tr("暂无此设备!"), QMessageBox::Ok);
    }

}
