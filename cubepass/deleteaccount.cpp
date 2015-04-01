#include "deleteaccount.h"
#include "ui_deleteaccount.h"

DeleteAccount::DeleteAccount(std::string username) :
    ui(new Ui::DeleteAccount),
    _username(username),
    _datFile(DAT_FILE),
    _deletedAccount(false)
{
    ui->setupUi(this);
}

DeleteAccount::~DeleteAccount()
{
    delete ui;
}

void DeleteAccount::on_edtConfirm_textChanged(const QString &arg1)
{
    ui->btnDelete->setEnabled(arg1 == "DELETE");
}

bool DeleteAccount::DeletedAccount()
{
    return _deletedAccount;
}

void DeleteAccount::on_btnCancel_clicked()
{
    this->close();
}
