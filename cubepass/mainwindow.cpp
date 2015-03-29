#include "mainwindow.h"
#include "loginscreen.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->ReLogin();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ReLogin()
{
    this->hide();
    LoginScreen newLogin;
    newLogin.exec();

    if (newLogin.LoggedIn())
    {
        _username = newLogin.returnUsername();
        _password = newLogin.returnPassword();
        //Update script
        this->show();
    }
    else
        this->close();
}
