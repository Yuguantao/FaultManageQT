#include "changestuinfo.h"
#include "ui_changestuinfo.h"
#include "mysql.h"

ChangeStuInfo::ChangeStuInfo(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChangeStuInfo)
{
    ui->setupUi(this);
    Sparent = (StuInfoManage*) parent;
}

ChangeStuInfo::~ChangeStuInfo()
{
    delete ui;
}

void ChangeStuInfo::on_buttonBox_clicked(QAbstractButton *button)
{
    if(ui->buttonBox->button(QDialogButtonBox::Ok) == button)
    {
        my_stu tran;

        tran.man_sys = ui->man_sys->text();
        tran.man_model = ui->man_model->text();
        tran.man_num = ui->man_num->text();
        tran.man_impTime = ui->man_impTime->date().toString("yyyy-MM-dd");
        tran.man_porpuse = ui->man_porpuse->text();
        tran.man_place = ui->man_place->text();
        tran.man_enclosure = ui->man_enclosure->text();
        tran.man_department = ui->man_department->text();
        tran.man_persion = ui->man_persion->text();
        tran.man_mfrspersion = ui->man_mfrspersion->text();
        tran.man_remarks = ui->man_remarks->toPlainText();

        QProgressDialog dialog(tr("正在修改"),tr("取消"), 0, 30000, this);
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
        bool ret = mysql.updatestu(&tran);
        if(ret == false)
        {
            QMessageBox::information(this, tr("消息"), tr("查无此人!"), QMessageBox::Ok);
            this->close();
            Sparent->show();
            return;
        }
        QMessageBox::information(this, tr("消息"), tr("修改成功!"), QMessageBox::Ok);
        this->close();
        Sparent->show();
        return;
    }
    else if(ui->buttonBox->button(QDialogButtonBox::Cancel) == button)
    {
        this->close();
        QProgressDialog dialog(tr("正在返回主界面"),tr("取消"), 0, 30000, this);
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
        Sparent->show();
    }
}
