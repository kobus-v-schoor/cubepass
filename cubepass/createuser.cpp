#include "createuser.h"
#include "ui_createuser.h"

CreateUser::CreateUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateUser),
    _iniFile(SETTINGS_FILE),
    _datFile(DAT_FILE)
{
    ui->setupUi(this);
    ui->lblWarning->hide();
    this->on_edtUsername_textChanged("");
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
    std::string username = ui->edtUsername->text().toStdString();
    std::string password = ui->edtPassword->text().toStdString();
    std::string message;
    if (_iniFile.AddProperty("Users", username, cube::Encryption(password, password)))
    {
        _datFile.CreateSection(username);
        _datFile.CreateVar(username, "Categories");
        _datFile.CreateVar(username, "Items");

        message = "User " + username + " successfully created.";
        QMessageBox msgB(QMessageBox::Information, "User created", message.c_str(),
                         QMessageBox::Ok);
        msgB.exec();
        _iniFile.ApplyChanges();
        _datFile.ApplyChanges();
        this->close();
    }
    else
    {
        message = "The user \"" + username + "\" already exists. Please choose another "
                "username.";
        QMessageBox msgB(QMessageBox::Warning, "User exists", message.c_str(),
                         QMessageBox::Ok);
        msgB.exec();
        ui->edtUsername->clear();
        ui->edtUsername->setFocus();
    }
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
        ui->lblWarning->setVisible(ui->edtPassword->text() != ui->edtCPword->text());
        ui->btnCreate->setEnabled(!(ui->edtPassword->text() != ui->edtCPword->text()));
    }
    else
        ui->lblWarning->hide();
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
