#include "mysql.h"

QSqlDatabase MySql::db;
MySql::MySql()
{

}

void MySql::initsql()
{
    db=QSqlDatabase::addDatabase("QSQLITE");
//    db.setHostName("127.0.0.1");
//    db.setUserName("root");
//    db.setPassword("!@#123");
    db.setDatabaseName("E:\\yuguantao\\ziliao\\qtdemo\\mydb.db");
    if(db.open())
        {
            qDebug()<<"Database connected successfully!";
            //createtable();
            return;
        }
    else
        {
            qDebug()<<"Database connected failed!";
            return;
        }
}


void MySql::createtable()
{
        query=new QSqlQuery;
        /*用户表*/
        query->exec("create table user(name VARCHAR(30) UNIQUE NOT NULL, passward VARCHAR(30), identify VARCHAR(30) PRIMARY KEY)");
        /*学生信息表*/
        query->exec("create table studentInfo(stuaccount VARCHAR(30) PRIMARY KEY UNIQUE NOT NULL, stuname VARCHAR(30), stusex ENUM('男', '女') NOT NULL, stuage INT, identify VARCHAR(30) UNIQUE NOT NULL, tel VARCHAR(20), enroll_time DATE, leave_time DATE, scondition enum('学习', '结业', '退学'), stu_text TEXT)");
        /*体检信息表*/
        query->exec("create table healthInfo(stuaccount VARCHAR(30) PRIMARY KEY UNIQUE NOT NULL, stuname VARCHAR(30) NOT NULL, height FLOAT, weight FLOAT, differentiate ENUM('正常', '色弱', '色盲'), left_sight FLOAT, right_sight FLOAT, left_ear ENUM('正常','偏弱'), right_ear ENUM('正常','偏弱'), legs ENUM('正常','不相等'), pressure ENUM('正常','偏高','偏低'), history VARCHAR(50), h_text TEXT)");
        /*考试课程表*/
        query->exec("create table courseInfo(classid INT PRIMARY KEY UNIQUE NOT NULL AUTO_INCREMENT, classname VARCHAR(30), beforeclassid INT)");
        /*考试成绩表*/
        query->exec("create table gradeInfo(stuaccount VARCHAR(30) PRIMARY KEY UNIQUE NOT NULL, classid INT NOT NULL, lasttime date, times INT default 1, grade float default 0, constraint grade_acc_fk FOREIGN KEY(stuaccount) REFERENCES studentInfo(stuaccount), constraint grade_cid_fk FOREIGN KEY(classid) REFERENCES courseInfo(classid))");
        /*领证时间表*/
        query->exec("create table licenseInfo(stuaccount VARCHAR(30) PRIMARY KEY UNIQUE NOT NULL, stuname VARCHAR(30), recv_time date, recv_name VARCHAR(30), l_text TEXT);");

        /*创建root用户*/
        query->exec("insert into user value('root', 'root', 'root')");

        /*学生表姓名索引*/
        query->exec("create index int_name ON studentInfo(stuname)");
        /*学生表学习状态索引*/
        query->exec("alter table studentInfo ADD INDEX ind_con(scondition)");
        /*体检表姓名索引*/
        query->exec("create index ind_hname ON healthInfo(stuname)");
        /*领证表姓名索引*/
        query->exec("alter table licenseInfo ADD INDEX ind_lname(stuname)");
        /*领证表领证人索引*/
        query->exec("alter table licenseInfo ADD INDEX ind_recvname(recv_name)");

        /*设计视图*/
        query->exec("create VIEW grade_view AS SELECT g.stuaccount, s.stuname, c.classname, g.lasttime, g.times, g.grade FROM studentinfo s, courseinfo c, gradeinfo g WHERE g.stuaccount = s.stuaccount AND g.classid = c.classid");

        /*设计insert触发器*/
        query->exec("CREATE TRIGGER license_stu AFTER INSERT ON licenseInfo  FOR EACH ROW BEGIN UPDATE studentInfo SET leave_time=NEW.recv_time, scondition = '结业' WHERE stuaccount = NEW.stuaccount; END");

        /*设计update触发器*/
        query->exec("CREATE TRIGGER update_name AFTER UPDATE ON studentinfo FOR EACH ROW BEGIN UPDATE healthinfo SET stuname = NEW.stuname WHERE stuaccount = NEW.stuaccount;END");

        /*设计delete触发器*/
        query->exec("CREATE TRIGGER delete_stu AFTER DELETE ON studentinfo FOR EACH ROW BEGIN DELETE FROM gradeinfo WHERE stuaccount = OLD.stuaccount; DELETE FROM healthinfo WHERE stuaccount = OLD.stuaccount; DELETE FROM licenseinfo WHERE stuaccount = OLD.stuaccount;END");
}


bool MySql::inituser(QString man_sys, QString man_model, QString man_num)
{
    query=new QSqlQuery;
    QString str=QString("insert into user value('%1','%2','%3')").arg(man_sys).arg(man_model).arg(man_num);
    bool ret=query->exec(str);
    return ret;
}



bool MySql::addstu(my_stu *stu)
{
    query=new QSqlQuery(db);

    QString mansys = stu->uuid;

    mansys.remove(0,1);
    mansys.remove(mansys.length() - 1, 1);

    QString str=QString("INSERT INTO faultdbmanage_managetable VALUES (\"%1\",\"%2\",\"%3\",\"%4\",\"%5\",\"%6\",\"%7\",\"%8\",\"%9\",\"%10\",\"%11\",\"%12\",\"%13\",\"%14\",\"%15\",\"%16\")").arg(60).arg(mansys).arg(stu->man_sys)
            .arg(stu->man_model).arg(stu->man_num).arg(stu->man_impTime).arg(stu->man_porpuse).arg("man_qualifi").arg(stu->man_place).arg(stu->man_enclosure).arg(stu->man_department).arg(stu->man_persion).arg(stu->man_mfrs).arg(stu->man_mfrspersion).arg(stu->man_impTime).arg(stu->man_remarks);
    bool ret=query->exec(str);
    return ret;
}

bool MySql::addfau(my_fau *stu)
{
    query=new QSqlQuery(db);

    QString mansys = stu->uuid;

    mansys.remove(0,1);
    mansys.remove(mansys.length() - 1, 1);

    QString str=QString("INSERT INTO faultdbmanage_faulttable VALUES (\"%1\",\"%2\",\"%3\",\"%4\",\"%5\",\"%6\",\"%7\",\"%8\",\"%9\",\"%10\",\"%11\",\"%12\",\"%13\",\"%14\",\"%15\",\"%16\")")
            .arg(mansys).arg(stu->fau_manInfo).arg(stu->fau_manInfo).arg(stu->fau_time)
            .arg(stu->fau_phen).arg(stu->fau_desc).arg(stu->fau_type).arg(stu->fau_num)
            .arg(stu->fau_reason).arg(stu->fau_effect).arg(stu->fau_check).arg(stu->fau_measure)
            .arg(stu->fau_advise).arg(stu->fau_peopleInfo).arg(stu->fau_time).arg(stu->fau_remarks);
    bool ret=query->exec(str);
    return ret;
}

bool MySql::updatestu(my_stu *stu)
{

}


bool MySql::deletestu(QString man_sys)
{
    query=new QSqlQuery;
    QString str=QString("select * from studentInfo where stuaccount='%1'").arg(man_sys);
    query->exec(str);
    query->last();
    int record=query->at()+1;
    if(record==0)
        return false;
    str=QString("delete from studentInfo where stuaccount='%1'").arg(man_sys);
    bool ret=query->exec(str);
    return ret;
}

bool MySql::selectfau(my_stu *stu)
{

}
