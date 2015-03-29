#include "mainwindow.h"
#include "loginscreen.h"
#include "ui_mainwindow.h"

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
    std::string itemsVar = _datFile.ReturnVar(_username, "Items");
    if (itemsVar == "empty")
        itemsVar.clear();

    for (int i = 0; i < itemsVar.size(); i++)
    {
        std::string temp;
        for (; (i < itemsVar.size()) && (itemsVar[i] != ';'); i++)
            temp += itemsVar[i];

        ui->lstItems->addItem(temp.c_str());
    }
}
