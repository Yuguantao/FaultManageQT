#include "dialog.h"
#include "ui_dialog.h"
#include "mysql.h"
#include "manage.h"
#include <QApplication>
#include <QDebug>
#include <QString>
#include <QSqlDatabase>
#include <QSqlError>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::getIpValue(QString index){

    ipValue = index;
}

void Dialog::on_inputMana_clicked()
{
    {
        QSqlDatabase pb;

        if (QSqlDatabase::contains("mysql")) {
            pb = QSqlDatabase::database("mysql");
        } else {
            pb = QSqlDatabase::addDatabase("QMYSQL", "mysql");
        }

        pb.setHostName(ipValue);
        pb.setUserName("root");
        pb.setPassword("123456");
        pb.setDatabaseName("defaultdb");

        if(pb.open())
            {

                QSqlQuery query(MySql::getDb());

                bool ret = query.exec("delete from faultdbmanage_managetable");

                if(ret){

                    QSqlQuery query1(pb);

                    if(!query1.exec("select * from faultdbmanage_managetable"))
                    {
                        qDebug() << query1.lastError();
                    }

                    int counts = 0;

                    if(query1.last())
                    {
                        counts =  query1.at() + 1;
                        query1.first();
                        query1.previous();
                    }

                    while(query1.next())
                    {
                        QString str=QString("INSERT INTO faultdbmanage_managetable VALUES (\"%1\",\"%2\",\"%3\",\"%4\",\"%5\",\"%6\",\"%7\",\"%8\",\"%9\",\"%10\",\"%11\",\"%12\",\"%13\",\"%14\",\"%15\",\"%16\")")
                                .arg(query1.value(0).toString())
                                .arg(query1.value(1).toString())
                                .arg(query1.value(2).toString())
                                .arg(query1.value(3).toString())
                                .arg(query1.value(4).toString())
                                .arg(query1.value(5).toString())
                                .arg(query1.value(6).toString())
                                .arg(query1.value(7).toString())
                                .arg(query1.value(8).toString())
                                .arg(query1.value(9).toString())
                                .arg(query1.value(10).toString())
                                .arg(query1.value(11).toString())
                                .arg(query1.value(12).toString())
                                .arg(query1.value(13).toString())
                                .arg(query1.value(14).toString())
                                .arg(query1.value(15).toString());
                        query.exec(str);

                    }

                    QProgressDialog dialog(tr("正在导入"),tr("取消"), 0, counts, this);
                    dialog.setWindowTitle(tr("进度"));
                    dialog.setWindowModality(Qt::WindowModal);
                    dialog.show();
                    for(int k = 0; k < counts; k++)
                    {
                        dialog.setValue(k);
                        QCoreApplication::processEvents();
                        if(dialog.wasCanceled())
                        {
                            break;
                        }
                    }
                    dialog.setValue(counts);
                    QMessageBox::information(this, tr("消息"), tr("导入成功!"), QMessageBox::Ok);

                }

            }
        else
            {
                qDebug()<<"Database connected failed!";
                return;
            }


    }
}

void Dialog::on_inputFault_clicked()
{
    {
        QSqlDatabase pb;

        if (QSqlDatabase::contains("mysql")) {
            pb = QSqlDatabase::database("mysql");
        } else {
            pb = QSqlDatabase::addDatabase("QMYSQL", "mysql");
        }

        pb.setHostName(ipValue);
        pb.setUserName("root");
        pb.setPassword("123456");
        pb.setDatabaseName("defaultdb");

        if(pb.open())
            {

                QSqlQuery query(MySql::getDb());

                bool ret = query.exec("delete from faultdbmanage_faulttable");

                if(ret){

                    QSqlQuery query1(pb);

                    if(!query1.exec("select * from faultdbmanage_faulttable"))
                    {
                        qDebug() << query1.lastError();
                    }

                    int counts = 0;

                    if(query1.last())
                    {
                        counts =  query1.at() + 1;
                        query1.first();
                        query1.previous();
                    }

                    while(query1.next())
                    {
                        QString str=QString("INSERT INTO faultdbmanage_faulttable VALUES (\"%1\",\"%2\",\"%3\",\"%4\",\"%5\",\"%6\",\"%7\",\"%8\",\"%9\",\"%10\",\"%11\",\"%12\",\"%13\",\"%14\",\"%15\",\"%16\")")
                                .arg(query1.value(0).toString())
                                .arg(query1.value(1).toString())
                                .arg(query1.value(2).toString())
                                .arg(query1.value(3).toString())
                                .arg(query1.value(4).toString())
                                .arg(query1.value(5).toString())
                                .arg(query1.value(6).toString())
                                .arg(query1.value(7).toString())
                                .arg(query1.value(8).toString())
                                .arg(query1.value(9).toString())
                                .arg(query1.value(10).toString())
                                .arg(query1.value(11).toString())
                                .arg(query1.value(12).toString())
                                .arg(query1.value(13).toString())
                                .arg(query1.value(14).toString())
                                .arg(query1.value(15).toString());
                        query.exec(str);
                    }

                    QProgressDialog dialog(tr("正在导入"),tr("取消"), 0, counts, this);
                    dialog.setWindowTitle(tr("进度"));
                    dialog.setWindowModality(Qt::WindowModal);
                    dialog.show();
                    for(int k = 0; k < counts; k++)
                    {
                        dialog.setValue(k);
                        QCoreApplication::processEvents();
                        if(dialog.wasCanceled())
                        {
                            break;
                        }
                    }
                    dialog.setValue(counts);
                    QMessageBox::information(this, tr("消息"), tr("导入成功!"), QMessageBox::Ok);

                }

            }
        else
            {
                qDebug()<<"Database connected failed!";
                return;
            }


    }
}
