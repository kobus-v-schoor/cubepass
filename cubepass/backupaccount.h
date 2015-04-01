#ifndef BACKUPACCOUNT_H
#define BACKUPACCOUNT_H

#include <QDialog>
#include "stdafx.h"

namespace Ui {
class BackupAccount;
}

class BackupAccount : public QDialog
{
    Q_OBJECT

public:
    explicit BackupAccount(QWidget* parent, std::string username);
    ~BackupAccount();

private slots:


    void on_btnCancel_clicked();

    void on_btnBrowse_clicked();

    void on_btnBackup_clicked();

private:
    Ui::BackupAccount *ui;
    std::string _username;
    cube::dataBase _datFile;
};

#endif // BACKUPACCOUNT_H
