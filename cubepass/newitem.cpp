#include "newitem.h"
#include "ui_newitem.h"
#include "stdafx.h"

NewItem::NewItem(std::string username, std::string password) :
    ui(new Ui::NewItem),
    _username(username),
    _password(password),
    _datFile(DAT_FILE)
{
    ui->setupUi(this);

    std::string _categories = _datFile.ReturnVar(_username, "Categories");
    if (_categories == "empty")
        _categories.clear();

    for (int i = 0; i < _categories.size(); i++)
    {
        std::string temp;
        for (; (i < _categories.size()) && (_categories[i] != ';'); i++)
            temp += _categories[i];
        ui->cmbCategory->addItem(temp.c_str());
    }

    ui->lblWarning->setVisible(false);
    ui->btnCreate->setEnabled(false);
    ui->edtUsername->setEnabled(false);
    ui->edtPassword->setEnabled(false);
    ui->edtCPassword->setEnabled(false);
    ui->cmbCategory->setEnabled(false);
}

NewItem::~NewItem()
{
    delete ui;
}

void NewItem::on_edtItemName_textChanged(const QString &arg1)
{
    if (ui->edtItemName->text().isEmpty())
    {
        ui->edtUsername->clear();
        ui->edtUsername->setEnabled(false);
    }
    else
        ui->edtUsername->setEnabled(true);
}

void NewItem::on_edtUsername_textChanged(const QString &arg1)
{
    if (ui->edtUsername->text().isEmpty())
    {
        ui->edtPassword->clear();
        ui->edtPassword->setEnabled(false);
    }
    else
        ui->edtPassword->setEnabled(true);
}

void NewItem::on_edtPassword_textChanged(const QString &arg1)
{
    ui->edtCPassword->clear();
    if (ui->edtPassword->text().isEmpty())
    {
        ui->edtCPassword->clear();
        ui->edtCPassword->setEnabled(false);
    }
    else
        ui->edtCPassword->setEnabled(true);
}

void NewItem::on_edtCPassword_textChanged(const QString &arg1)
{
    if ((ui->edtPassword->text().length() - ui->edtCPassword->text().length()) <= 3)
    {
        ui->lblWarning->setVisible(ui->edtPassword->text() != ui->edtCPassword->text());
        ui->cmbCategory->setEnabled(ui->edtPassword->text() == ui->edtCPassword->text());
        ui->btnCreate->setEnabled(ui->edtPassword->text() == ui->edtCPassword->text());
    }
    else
    {
        ui->lblWarning->hide();
        ui->btnCreate->setEnabled(false);
    }
}

void NewItem::on_chckShowPword_toggled(bool checked)
{
    if (checked)
    {
        ui->edtPassword->setEchoMode(QLineEdit::Normal);
        ui->edtCPassword->setEchoMode(QLineEdit::Normal);
    }
    else
    {
        ui->edtPassword->setEchoMode(QLineEdit::Password);
        ui->edtCPassword->setEchoMode(QLineEdit::Password);
    }
}

void NewItem::on_btnCancel_clicked()
{
    this->close();
}

void NewItem::on_btnCreate_clicked()
{
    std::string _items = _datFile.ReturnVar(_username, "Items");
    if (_items == "empty")
        _items.clear();

    std::string sectionName = _username + "/" + ui->edtItemName->text().toStdString();
    if (!_datFile.CreateSection(sectionName))
    {
        QMessageBox msgB(QMessageBox::Warning, "Item exists", "This item name you specified "
                         "already exists. Please choose another.", QMessageBox::Ok);
        msgB.exec();
        ui->edtItemName->clear();
    }
    else
    {
        _items += ui->edtItemName->text().toStdString() + ";";
        _datFile.ChangeVarValue(_username, "Items", _items);

        _datFile.CreateVar(sectionName, "ItemName", ui->edtItemName->text().toStdString());
        _datFile.CreateVar(sectionName, "Category", ui->cmbCategory->currentText().toStdString());
        _datFile.CreateVar(sectionName, "Username", cube::Encryption(ui->edtUsername->text().toStdString(),
                                                                     _password));
        _datFile.CreateVar(sectionName, "Password", cube::Encryption(ui->edtPassword->text().toStdString(),
                                                                     _password));
        _datFile.ApplyChanges();
        this->close();
    }
}
