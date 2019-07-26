#include "addinfo.h"
#include "ui_addinfo.h"
#include "mysql.h"
#include "stuinfomanage.h"

AddInfo::AddInfo(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AddInfo)
{
    Sparent=(StuInfoManage*) parent;
    ui->setupUi(this);

     connect(this, &AddInfo::upDate, Sparent, &StuInfoManage::tabletimeslot);
}

AddInfo::~AddInfo()
{
    delete ui;
}

void AddInfo::on_buttonBox_clicked(QAbstractButton *button)
{
    if(ui->buttonBox->button(QDialogButtonBox::Ok) == button)
    {
        my_stu tran;
        QUuid id = QUuid::createUuid();
        tran.uuid = id.toString();
        tran.man_sys = ui->man_sys->text();
        tran.man_model = ui->man_model->text();
        tran.man_num = ui->man_num->text();
        tran.man_impTime = ui->man_impTime->date().toString("yyyy-MM-dd");
        tran.man_porpuse = ui->man_porpuse->text();
        tran.man_place = ui->man_place->text();
        tran.man_enclosure = ui->man_enclosure->text();
        tran.man_department = ui->man_department->text();
        tran.man_mfrs = ui->man_mfrs->text();
        tran.man_persion = ui->man_persion->text();
        tran.man_mfrspersion = ui->man_mfrspersion->text();
        tran.man_remarks = ui->man_remarks->toPlainText();

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
        bool ret = mysql.addstu(&tran);
        if(ret == false)
        {
            QMessageBox::information(this, tr("消息"), tr("添加失败!"), QMessageBox::Ok);
            this->close();
            Sparent->show();
            return;
        }
        QMessageBox::information(this, tr("消息"), tr("添加成功!"), QMessageBox::Ok);
        Sparent->tabletimeslot();
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
