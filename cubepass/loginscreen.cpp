#include "loginscreen.h"
#include "ui_loginscreen.h"
#include "createuser.h"
#include "restoreaccount.h"

LoginScreen::LoginScreen(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::LoginScreen),
	_iniFile(SETTINGS_FILE),
	_loggedIn(false)
{
	ui->setupUi(this);
	ui->lblWarning->hide();
}

LoginScreen::~LoginScreen()
{
	delete ui;
}

void LoginScreen::on_edtUsername_textChanged(const QString &arg1)
{
	if (ui->edtUsername->text().isEmpty() || ui->edtPassword->text().isEmpty())
		ui->btnLogin->setEnabled(false);
	else
		ui->btnLogin->setEnabled(true);
}

void LoginScreen::on_edtPassword_textChanged(const QString &arg1)
{
	if (ui->edtUsername->text().isEmpty() || ui->edtPassword->text().isEmpty())
		ui->btnLogin->setEnabled(false);
	else
		ui->btnLogin->setEnabled(true);
}

void LoginScreen::on_btnLogin_clicked()
{
	ui->lblWarning->hide();
	this->_username = ui->edtUsername->text().toStdString();
	this->_password = ui->edtPassword->text().toStdString();
	std::string _compareStr = _iniFile.ReturnValue("Users", _username);
	if (!_compareStr.empty())
	{
		_loggedIn = (cube::Decryption(_compareStr, _password) ==
					 _password);

		if (_loggedIn)
			this->close();
		else
		{
			ui->lblWarning->setText("Decrypting...");
			ui->lblWarning->show();
			this->SetAllButtonsState(false);
			this->setCursor(Qt::BusyCursor);
			std::this_thread::sleep_for(std::chrono::milliseconds(2500));
			this->setCursor(Qt::ArrowCursor);
			this->SetAllButtonsState(true);
			ui->lblWarning->setText("Incorrect password");
		}
	}
	else
	{
		std::string message = "The user \"" + _username + "\" does not exist. "
				"To create a new user click on the \"Create user\" button "
				"on the login screen.";
		QMessageBox msgB(QMessageBox::Warning, "User does not exist", message.c_str(),
						 QMessageBox::Ok, this);
		msgB.exec();
		ui->edtUsername->clear();
		ui->edtPassword->clear();
		ui->edtUsername->setFocus();
	}
}

void LoginScreen::on_btnCreate_clicked()
{
	CreateUser newUser(this);
	newUser.exec();
	this->_iniFile.Reparse();
	ui->edtUsername->setFocus();
}

void LoginScreen::on_btnRestore_clicked()
{
	RestoreAccount restoreAccount(this);
	restoreAccount.exec();
	_iniFile.Reparse();
}

bool LoginScreen::LoggedIn()
{
	return _loggedIn;
}

std::string LoginScreen::returnUsername()
{
	return _username;
}

std::string LoginScreen::returnPassword()
{
	return _password;
}

void LoginScreen::SetAllButtonsState(bool state)
{
	ui->btnCreate->setEnabled(state);
	ui->btnRestore->setEnabled(state);
	ui->btnLogin->setEnabled(state);
	qApp->processEvents();
}
