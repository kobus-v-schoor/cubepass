#include "restoreuserexists.h"
#include "ui_restoreuserexists.h"

RestoreUserExists::RestoreUserExists(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RestoreUserExists),
    _datFile(DAT_FILE),
    _replace(false),
    _changed(false)
{
    ui->setupUi(this);
    ui->edtNewUser->hide();
}

RestoreUserExists::~RestoreUserExists()
{
    delete ui;
}

void RestoreUserExists::on_btnChange_clicked()
{
    if (!ui->edtNewUser->isVisible())
    {
        ui->btnChange->setEnabled(false);
        ui->edtNewUser->show();
        ui->btnReplace->setEnabled(false);
        ui->edtNewUser->setFocus();
        return;
    }

    if (!_datFile.CreateSection(ui->edtNewUser->text().toStdString()))
    {
        QMessageBox msgB(QMessageBox::Warning, "User exists",
                         "The username you specified already exists. "
                         "Please choose another.", QMessageBox::Ok);
        msgB.exec();
        return;
    }
    _newUsername = ui->edtNewUser->text().toStdString();
    _changed = true;
    this->close();
}

bool RestoreUserExists::Replaced()
{
    return _replace;
}

bool RestoreUserExists::Changed()
{
    return _changed;
}

std::string RestoreUserExists::ReturnNewUsername()
{
    return _newUsername;
}

void RestoreUserExists::on_edtNewUser_textChanged(const QString &arg1)
{
    ui->btnChange->setEnabled(!arg1.isEmpty());
}

void RestoreUserExists::on_btnReplace_clicked()
{
    _replace = true;
    this->close();
}

void RestoreUserExists::on_btnCancel_clicked()
{
    this->close();
}
