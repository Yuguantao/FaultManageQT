#include "manage.h"
#include "stuinfomanage.h"
#include "fault.h"
#include "ui_manage.h"
#include "mysql.h"
#include "dialog.h"
#include "dialogexport.h"

#include <QApplication>
#include <QFileDialog>
#include <QDebug>
#include <QString>
#include <QProcess>
#include <QSqlDatabase>
#include <QSqlError>


Manage::Manage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Manage)
{
    ui->setupUi(this);
    ui->pushButton->hide();
    ui->pushButton_2->hide();
    ui->ipBox->setPlaceholderText("请输入IP地址!");
}

Manage::~Manage()
{
    delete ui;
}

void Manage::on_stuInfo_clicked()
{
    this->hide();
    StuInfoManage *SIM=new StuInfoManage(this);
    SIM->setWindowTitle("设备信息");
    SIM->show();

}


void Manage::on_liceInfo_clicked()
{
    this->hide();
    fault *SIM=new fault(this);
    SIM->show();
}

void Manage::on_pushButton_clicked()
{

    Dialog *SIM=new Dialog(this);
    SIM->getIpValue(IpValue);
    SIM->show();
}

void Manage::on_pushButton_2_clicked()
{
    DialogExport *SIM=new DialogExport(this);
    SIM->getIpValue(IpValue);
    SIM->show();
}

void Manage::on_connectBtn_clicked()
{
    QProcess cmd;
    QProgressDialog dialog(tr("正在连接"),tr("取消"), 0, 30000, this);
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

    QString ping;


    if(ui->ipBox->text()!= ""){
        ping = "ping " + ui->ipBox->text();
    }else{
        ping = "";
    }

    IpValue = ui->ipBox->text();

    cmd.start(ping);
    cmd.waitForReadyRead(1000);
    cmd.waitForFinished(1000);

    QString response = cmd.readAll();

    if (response.indexOf("TTL") == -1)
    {
        QMessageBox::information(this, tr("消息"), tr("连接失败!"), QMessageBox::Ok);
    }
    else
    {
        QMessageBox::information(this, tr("消息"), tr("连接成功!"), QMessageBox::Ok);
        ui->connectBtn->hide();
        ui->ipBox->hide();
        ui->pushButton->show();
        ui->pushButton_2->show();
    }
}
