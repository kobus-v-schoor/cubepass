#include "createuser.h"
#include "ui_createuser.h"

CreateUser::CreateUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateUser),
    _iniFile("settings.ini"),
    _datFile("usersdata.dat")
{
    ui->setupUi(this);
    ui->lblWarning->hide();
}

CreateUser::~CreateUser()
{
    delete ui;
}

void CreateUser::on_btnCancel_clicked()
{
    this->close();
}

void CreateUser::on_btnCreate_clicked()
{
    //
}

void CreateUser::on_edtPassword_textChanged(const QString &arg1)
{
    if (ui->edtPassword->text().isEmpty())
    {
        ui->edtCPword->setEnabled(false);
        ui->btnCreate->setEnabled(false);
    }
    else
        ui->edtCPword->setEnabled(true);

    ui->edtCPword->clear();
}

void CreateUser::on_edtCPword_textChanged(const QString &arg1)
{
    if ((ui->edtPassword->text().length() - ui->edtCPword->text().length()) <= 3)
    {
        if (ui->edtPassword->text() != ui->edtCPword->text())
            ui->lblWarning->setVisible(true);
        else
        {
            ui->lblWarning->setVisible(false);
            ui->btnCreate->setEnabled(true);
        }
    }
}

void CreateUser::on_edtUsername_textChanged(const QString &arg1)
{
    if (ui->edtUsername->text().isEmpty())
    {
        ui->edtPassword->clear();
        this->on_edtPassword_textChanged("");
        ui->edtPassword->setEnabled(false);
    }
    else
    {
        ui->edtPassword->setEnabled(true);
    }
}
