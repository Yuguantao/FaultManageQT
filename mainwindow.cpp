#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "register.h"
#include "logging.h"
#include "manage.h"
#include "mysql.h"
#include <QInputDialog>

MainWindow * MainWindow::MW=NULL;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow *MainWindow::getIntance()
{
    if(MW == NULL)
    {
        MW = new MainWindow();
    }
    return MW;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loginBtn_clicked()
{
    this->hide();
    logging *log=new logging(this);
    log->setWindowTitle("登录");
    log->show();
}


void MainWindow::on_exitBtn_clicked()
{
    this->close();
}
