#include "stdafx.h"
#include "loginscreen.h"
#include "ui_loginscreen.h"

LoginScreen::LoginScreen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginScreen),
    _iniFile("settings.ini"),
    _loggedIn(false)
{
    ui->setupUi(this);
    ui->lblWarning->hide();
}

LoginScreen::~LoginScreen()
{
    delete ui;
}

void LoginScreen::on_edtUsername_textChanged(const QString &arg1)
{
    if (ui->edtUsername->text().isEmpty() || ui->edtPassword->text().isEmpty())
        ui->btnLogin->setEnabled(false);
    else
        ui->btnLogin->setEnabled(true);
}

void LoginScreen::on_edtPassword_textChanged(const QString &arg1)
{
    if (ui->edtUsername->text().isEmpty() || ui->edtPassword->text().isEmpty())
        ui->btnLogin->setEnabled(false);
    else
        ui->btnLogin->setEnabled(true);
}

void LoginScreen::on_btnLogin_clicked()
{
    //Login code here
}

void LoginScreen::on_btnCreate_clicked()
{
    //Create text here
}

void LoginScreen::on_btnRestore_clicked()
{
    //Restore window open
}

bool LoginScreen::LoggedIn()
{
    return _loggedIn;
}

std::string LoginScreen::returnUsername()
{
    return _username;
}

std::string LoginScreen::returnPassword()
{
    return _password;
}
