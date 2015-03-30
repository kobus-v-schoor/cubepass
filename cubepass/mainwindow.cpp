#include "mainwindow.h"
#include "loginscreen.h"
#include "ui_mainwindow.h"
#include "newitem.h"
#include "itemdetails.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _datFile(DAT_FILE)
{
    ui->setupUi(this);
    this->ReLogin();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ReLogin()
{
    this->hide();
    LoginScreen newLogin;
    newLogin.exec();

    if (newLogin.LoggedIn())
    {
        _username = newLogin.returnUsername();
        _password = newLogin.returnPassword();

        this->UpdateCategories();
        this->UpdateItems();
        this->show();
    }
    else
        this->close();
}

void MainWindow::UpdateCategories()
{
    ui->cmbCategory->clear();
    ui->cmbCategory->addItem("All");
    this->_datFile.Reparse();
    std::string catVar = _datFile.ReturnVar(_username, "Categories");
    if (catVar == "empty")
        catVar.clear();

    for (int i = 0; i < catVar.size(); i++)
    {
        std::string temp;
        for (;(i < catVar.size()) && (catVar[i] != ';'); i++)
            temp += catVar[i];

        ui->cmbCategory->addItem(temp.c_str());
    }
}

void MainWindow::UpdateItems()
{
    ui->lstItems->clear();
    this->_datFile.Reparse();
    std::string itemsVar = _datFile.ReturnVar(_username, "Items");
    if (itemsVar == "empty")
        itemsVar.clear();

    for (int i = 0; i < itemsVar.size(); i++)
    {
        std::string temp;
        for (; (i < itemsVar.size()) && (itemsVar[i] != ';'); i++)
            temp += itemsVar[i];

        if (ui->cmbCategory->currentText() == "All")
            ui->lstItems->addItem(temp.c_str());
        else
        {
            if (ui->cmbCategory->currentText().toStdString() ==
                    _datFile.ReturnVar(_username + "/" + temp, "Category"))
                ui->lstItems->addItem(temp.c_str());
        }
    }
}

void MainWindow::on_btnNewItem_clicked()
{
    NewItem newItem(_username, _password);
    newItem.exec();

    this->UpdateItems();
}

void MainWindow::on_cmbCategory_currentIndexChanged(int index)
{
    this->UpdateItems();
}

void MainWindow::on_lstItems_itemDoubleClicked(QListWidgetItem *item)
{
    ItemDetails newDetails(item->text().toStdString(), _username, _password);
    newDetails.exec();

    this->UpdateItems();
}
