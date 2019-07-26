#include "dialogexport.h"
#include "ui_dialogexport.h"
#include "mysql.h"
#include "manage.h"
#include <QApplication>
#include <QDebug>
#include <QString>
#include <QSqlDatabase>
#include <QSqlError>

DialogExport::DialogExport(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogExport)
{
    ui->setupUi(this);
}

DialogExport::~DialogExport()
{
    delete ui;
}

void DialogExport::getIpValue(QString index){

    ipValue = index;
}

void DialogExport::on_ExputMana_clicked()
{
    QMessageBox::StandardButton reply;

    reply  =  QMessageBox::information(NULL, "Title", "是否覆盖",QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

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

            bool ret = query.exec("select * from faultdbmanage_managetable");

            if(ret){

                QSqlQuery query1(pb);

                int counts = 0;

                if(query.last())
                {
                    counts =  query.at() + 1;
                    query.first();
                    query.previous();
                }

                while(query.next())
                {
                    QString selectStr = QString("select 1 from faultdbmanage_managetable where man_sys = '%1' and man_model = '%2' and man_num= '%3' limit 1;")
                            .arg(query.value(2).toString())
                            .arg(query.value(3).toString())
                            .arg(query.value(4).toString());

                    query1.exec(selectStr);

                    int t = 60;

                    bool flag;

                    if(query1.next()) {

                        flag = query1.value(0).toBool();
                    }


                    qDebug() << flag;

                    if(flag){

                       if( reply == QMessageBox::Yes ){

                           QString str=QString("UPDATE faultdbmanage_managetable SET man_impTime='%4',man_porpuse='%5',man_qualifi='%6',man_place='%7',man_enclosure='%8',man_department='%9',man_persion='%10',man_mfrs='%11',man_mfrspersion='%12',man_remarks='%14' WHERE man_sys = '%1' and man_model = '%2' and man_num= '%3'")
                                   .arg(query.value(2).toString())
                                   .arg(query.value(3).toString())
                                   .arg(query.value(4).toString())
                                   .arg(query.value(5).toString())
                                   .arg(query.value(6).toString())
                                   .arg(query.value(7).toString())
                                   .arg(query.value(8).toString())
                                   .arg(query.value(9).toString())
                                   .arg(query.value(10).toString())
                                   .arg(query.value(11).toString())
                                   .arg(query.value(12).toString())
                                   .arg(query.value(13).toString())
                                   .arg(query.value(14).toString())
                                   .arg(query.value(15).toString());

                           query1.exec(str);
                           qDebug() << str;

                       }else{
                           continue;
                       }

                    }else {

                        QString str=QString("INSERT INTO faultdbmanage_managetable VALUES (\"%1\",\"%2\",\"%3\",\"%4\",\"%5\",\"%6\",\"%7\",\"%8\",\"%9\",\"%10\",\"%11\",\"%12\",\"%13\",\"%14\",\"%15\",\"%16\")")
                                .arg(t)
                                .arg(query.value(1).toString())
                                .arg(query.value(2).toString())
                                .arg(query.value(3).toString())
                                .arg(query.value(4).toString())
                                .arg(query.value(5).toString())
                                .arg(query.value(6).toString())
                                .arg(query.value(7).toString())
                                .arg(query.value(8).toString())
                                .arg(query.value(9).toString())
                                .arg(query.value(10).toString())
                                .arg(query.value(11).toString())
                                .arg(query.value(12).toString())
                                .arg(query.value(13).toString())
                                .arg(query.value(14).toString())
                                .arg(query.value(15).toString());

                        query1.exec(str);
                    }
                }

                QProgressDialog dialog(tr("正在导出"),tr("取消"), 0, counts, this);
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
                QMessageBox::information(this, tr("消息"), tr("导出成功!"), QMessageBox::Ok);

            }

        }
    else
        {
            qDebug()<<"Database connected failed!";
            return;
        }

}

void DialogExport::on_ExputFault_clicked()
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

            bool ret = query.exec("select * from faultdbmanage_faulttable");

            if(ret){

                QSqlQuery query1(pb);

                int counts = 0;

                if(query.last())
                {
                    counts =  query.at() + 1;
                    query.first();
                    query.previous();
                }

                while(query.next())
                {
                    QString selectStr = QString("select 1 from faultdbmanage_faulttable where uuid = '%1' limit 1;")
                            .arg(query.value(0).toString());

                    query1.exec(selectStr);

                    bool flag;

                    if(query1.next()) {

                        flag = query1.value(0).toBool();
                    }

                    if(!flag){

                        QString str=QString("INSERT INTO faultdbmanage_faulttable VALUES (\"%1\",\"%2\",\"%3\",\"%4\",\"%5\",\"%6\",\"%7\",\"%8\",\"%9\",\"%10\",\"%11\",\"%12\",\"%13\",\"%14\",\"%15\",\"%16\")")
                                .arg(query.value(0).toString())
                                .arg(query.value(1).toString())
                                .arg(query.value(2).toString())
                                .arg(query.value(3).toString())
                                .arg(query.value(4).toString())
                                .arg(query.value(5).toString())
                                .arg(query.value(6).toString())
                                .arg(query.value(7).toString())
                                .arg(query.value(8).toString())
                                .arg(query.value(9).toString())
                                .arg(query.value(10).toString())
                                .arg(query.value(11).toString())
                                .arg(query.value(12).toString())
                                .arg(query.value(13).toString())
                                .arg(query.value(14).toString())
                                .arg(query.value(15).toString());

                        query1.exec(str);
                    }
                }
                QProgressDialog dialog(tr("正在导出"),tr("取消"), 0, counts, this);
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
                QMessageBox::information(this, tr("消息"), tr("导出成功!"), QMessageBox::Ok);

            }

        }
    else
        {
            qDebug()<<"Database connected failed!";
            return;
        }

}
