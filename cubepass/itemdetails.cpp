#include "itemdetails.h"
#include "ui_itemdetails.h"

ItemDetails::ItemDetails(std::string itemName, std::string username, std::string password) :
    ui(new Ui::ItemDetails),
    _itemName(itemName),
    _username(username),
    _password(password),
    _datFile(DAT_FILE)
{
    ui->setupUi(this);
}

ItemDetails::~ItemDetails()
{
    delete ui;
}
