#ifndef ITEMDETAILS_H
#define ITEMDETAILS_H

#include <QDialog>
#include "stdafx.h"

namespace Ui {
class ItemDetails;
}

class ItemDetails : public QDialog
{
    Q_OBJECT

public:
    explicit ItemDetails(std::string itemName, std::string username,
                         std::string password);
    ~ItemDetails();

private slots:
    void on_chckShowPword_toggled(bool checked);

    void on_btnEdit_clicked();

    void on_btnDone_clicked();

private:
    Ui::ItemDetails *ui;
    std::string _username;
    std::string _password;
    std::string _itemName;
    cube::dataBase _datFile;
    bool _editing;
};

#endif // ITEMDETAILS_H
