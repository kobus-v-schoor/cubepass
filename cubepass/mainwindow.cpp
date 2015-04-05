#include "mainwindow.h"
#include "loginscreen.h"
#include "ui_mainwindow.h"
#include "newitem.h"
#include "itemdetails.h"
#include "categorymanager.h"
#include "deleteaccount.h"
#include "backupaccount.h"
#include "restoreaccount.h"
#include "changepword.h"

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
    LoginScreen newLogin(this);
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
    NewItem newItem(this, _username, _password);
    newItem.exec();

    this->UpdateItems();
}

void MainWindow::on_cmbCategory_currentIndexChanged(int index)
{
    this->UpdateItems();
}

void MainWindow::on_lstItems_itemDoubleClicked(QListWidgetItem *item)
{
    ItemDetails newDetails(this, item->text().toStdString(), _username, _password);
    newDetails.exec();

    this->UpdateItems();
}

void MainWindow::on_btnManageCt_clicked()
{
    CategoryManager newMan(this, _username);
    newMan.exec();

    this->UpdateCategories();
    this->UpdateItems();
}

void MainWindow::on_actionLogout_triggered()
{
    this->ReLogin();
}

void MainWindow::on_actionDelete_this_account_triggered()
{
    DeleteAccount deleteAccount(this, _username);
    deleteAccount.exec();

    if (deleteAccount.DeletedAccount())
        this->ReLogin();
}

void MainWindow::on_actionBackup_this_profile_triggered()
{
    BackupAccount _newBackup(this, _username);
    _newBackup.exec();
}

void MainWindow::on_actionRestore_a_profile_triggered()
{
    RestoreAccount newRestore(this);
    newRestore.exec();

    if (newRestore.RestoredAnAccount())
    {
        QMessageBox msgB(QMessageBox::Information, "Database modified",
                         "The database for CubePass has been modified. "
                         "Please re-login for changes to take effect.",
                         QMessageBox::Ok, this);
        msgB.exec();
        this->ReLogin();
    }
}

void MainWindow::on_actionChange_profile_password_triggered()
{
    ChangePword changePword(this, _username, _password);
    changePword.exec();
    if (changePword.PwordChanged())
        this->ReLogin();
}
