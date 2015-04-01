#ifndef NEWITEM_H
#define NEWITEM_H

#include <QDialog>
#include "stdafx.h"

namespace Ui {
class NewItem;
}

class NewItem : public QDialog
{
    Q_OBJECT

public:
    explicit NewItem(std::string username, std::string password);
    ~NewItem();

private slots:
    void on_edtItemName_textChanged(const QString &arg1);

    void on_edtUsername_textChanged(const QString &arg1);

    void on_edtPassword_textChanged(const QString &arg1);

    void on_chckShowPword_toggled(bool checked);

    void on_btnCancel_clicked();

    void on_btnCreate_clicked();

private:
    Ui::NewItem *ui;
    cube::dataBase _datFile;
    std::string _username;
    std::string _password;

    void updateBtnCreate();
};

#endif // NEWITEM_H
