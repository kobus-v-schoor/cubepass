#include "newitem.h"
#include "ui_newitem.h"

NewItem::NewItem(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewItem)
{
    ui->setupUi(this);
    ui->lblWarning->setVisible(false);
    ui->btnCreate->setEnabled(false);
    ui->edtUsername->setEnabled(false);
    ui->edtPassword->setEnabled(false);
    ui->edtCPassword->setEnabled(false);
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
