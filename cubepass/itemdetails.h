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

private:
    Ui::ItemDetails *ui;
    std::string _username;
    std::string _password;
    std::string _itemName;
    cube::dataBase _datFile;
};

#endif // ITEMDETAILS_H
