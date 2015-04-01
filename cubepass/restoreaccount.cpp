#include "restoreaccount.h"
#include "ui_restoreaccount.h"

RestoreAccount::RestoreAccount(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RestoreAccount)
{
    ui->setupUi(this);
}

RestoreAccount::~RestoreAccount()
{
    delete ui;
}
