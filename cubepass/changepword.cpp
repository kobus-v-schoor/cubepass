#include "changepword.h"
#include "ui_changepword.h"

ChangePword::ChangePword(QWidget *parent, std::string username, std::string password) :
    QDialog(parent),
    ui(new Ui::ChangePword),
    _username(username),
    _password(password),
    _datFile(DATABASE_FILE),
    _iniFile(SETTINGS_FILE),
    _pwordChanged(false)
{
    ui->setupUi(this);
    ui->lblWarning->hide();
}

ChangePword::~ChangePword()
{
    delete ui;
}

void ChangePword::on_edtPassword_textChanged(const QString &arg1)
{
    this->UpdateWarning();
}

void ChangePword::on_edtCPword_textChanged(const QString &arg1)
{
    this->UpdateWarning();
}

void ChangePword::UpdateWarning()
{
    if (((ui->edtPassword->text().length() -
         ui->edtCPword->text().length()) < 3) &&
            !ui->edtCPword->text().isEmpty())
    {
        ui->lblWarning->setVisible(ui->edtPassword->text() !=
                                  ui->edtCPword->text());
        ui->btnChange->setEnabled(ui->edtPassword->text() ==
                                  ui->edtCPword->text());
    }
    else
        ui->lblWarning->hide();
}

bool ChangePword::PwordChanged()
{
    return _pwordChanged;
}

void ChangePword::on_btnCancel_clicked()
{
    this->close();
}

void ChangePword::on_btnChange_clicked()
{
    std::string _items = _datFile.ReturnVar(_username, "Items");
    if (_items == "empty")
        _items.clear();

    for (int i = 0; i < _items.size(); i++)
    {
        std::string temp;
        for (; (i < _items.size()) && (_items[i] != ';'); i++)
            temp += _items[i];

        this->Recrypt("Username", temp);
        this->Recrypt("Password", temp);
    }

    _iniFile.ChangeProperty("Users", _username, cube::Encryption(ui->edtPassword->text().toStdString(),
                                                                 ui->edtPassword->text().toStdString()));
    _datFile.ApplyChanges();
    _iniFile.ApplyChanges();

    _pwordChanged = true;
    QMessageBox msgB(QMessageBox::Information, "Password changed", "Your password has been "
                "successfully changed. You will now be logged out in order to update your settings.",
                QMessageBox::Ok, this);
    msgB.exec();
    this->close();
}

void ChangePword::Recrypt(std::string var, std::string item)
{
    std::string temp = cube::Decryption(_datFile.ReturnVar(_username + "/" + item, var),
                                        _password);
    temp = cube::Encryption(temp, ui->edtPassword->text().toStdString());
    _datFile.ChangeVarValue(_username + "/" + item, var, temp);
}
