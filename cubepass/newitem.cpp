#include "newitem.h"
#include "ui_newitem.h"

NewItem::NewItem(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewItem)
{
    ui->setupUi(this);
}

NewItem::~NewItem()
{
    delete ui;
}
