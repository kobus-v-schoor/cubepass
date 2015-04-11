#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "loginscreen.h"
#include "newitem.h"
#include "itemdetails.h"
#include "categorymanager.h"
#include "deleteaccount.h"
#include "backupaccount.h"
#include "restoreaccount.h"
#include "changepword.h"
#include "aboutscreen.h"
#include "helpscreen.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	_iniFile(SETTINGS_FILE),
	_datFile(DATABASE_FILE),
	_statusText(new QLabel(this))
{
	ui->setupUi(this);

	if (_iniFile.ReturnValue("Startup", "ShowHelp") == "true")
		HelpScreen(this).exec();

	_statusText->setFrameStyle(QFrame::NoFrame);
	this->ReLogin();
}

MainWindow::~MainWindow()
{
	delete ui;
	delete _statusText;
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
		std::string temp = "Currently logged in as: " + _username;
		this->_statusText->setText(temp.c_str());
		ui->statusbar->clearMessage();
		ui->statusbar->addWidget(_statusText);
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

void MainWindow::on_btnCreateItem_clicked()
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

void MainWindow::on_actionDonate_triggered()
{
	QString donateUrl("https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=GHDMPQVJS8832");
	QDesktopServices::openUrl(QUrl(donateUrl));
}

void MainWindow::on_actionAbout_triggered()
{
	AboutScreen aboutScreen(this);
	aboutScreen.exec();
}

void MainWindow::on_actionHelp_triggered()
{
	HelpScreen(this).exec();
}
