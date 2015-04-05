#include "deleteaccount.h"
#include "ui_deleteaccount.h"

DeleteAccount::DeleteAccount(QWidget *parent, std::string username) :
    QDialog(parent),
    ui(new Ui::DeleteAccount),
    _username(username),
    _datFile(DAT_FILE),
    _iniFile(SETTINGS_FILE),
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

void DeleteAccount::on_btnDelete_clicked()
{
    QMessageBox msgB(QMessageBox::Question, "Are you sure?",
                     "This action cannot be undone.", QMessageBox::Yes |
                     QMessageBox::No, this);
    if (msgB.exec() == QMessageBox::No)
        return;

    _datFile.DeleteSection(_username);
    _iniFile.DeleteProperty("Users", _username);
    _datFile.ApplyChanges();
    _iniFile.ApplyChanges();
    _deletedAccount = true;
    this->close();
}
