#include "restoreuserexists.h"
#include "ui_restoreuserexists.h"

RestoreUserExists::RestoreUserExists(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RestoreUserExists),
    _datFile(DAT_FILE),
    _replaced(false),
    _changed(false),
    _canceled(false)
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
        return;
    }


}

bool RestoreUserExists::Replaced()
{
    return _replaced;
}

bool RestoreUserExists::Changed()
{
    return _changed;
}

bool RestoreUserExists::Cancelled()
{
    return _canceled;
}
