#include "categorymanager.h"
#include "ui_categorymanager.h"

CategoryManager::CategoryManager(std::string username) :
    ui(new Ui::CategoryManager)
{
    ui->setupUi(this);
}

CategoryManager::~CategoryManager()
{
    delete ui;
}
