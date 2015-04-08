#include "restoreaccount.h"
#include "ui_restoreaccount.h"
#include <QFileDialog>
#include "restoreuserexists.h"

RestoreAccount::RestoreAccount(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::RestoreAccount),
	_datFile(DATABASE_FILE),
	_iniFile(SETTINGS_FILE),
	_restoredSomething(false)
{
	ui->setupUi(this);
}

RestoreAccount::~RestoreAccount()
{
	delete ui;
}

void RestoreAccount::on_btnBrowse_clicked()
{
	QFileDialog openDialog;
	ui->edtFilepath->setText(openDialog.getOpenFileName(this, "Open backup file", "",
														"Backup files (*dat)"));
}

void RestoreAccount::on_btnCancel_clicked()
{
	this->close();
}

void RestoreAccount::on_btnRestore_clicked()
{
	std::string _filepath = ui->edtFilepath->text().toStdString();
	cube::dataBase _backup(_filepath);

	if (!_backup.IsParsed()){
		this->ShowError();
		return;
	}

	std::string _username = _backup.ReturnVar("User", "Username");
	std::string _password = _backup.ReturnVar("User", "Password");
	std::string _categories = _backup.ReturnVar("User", "Categories");
	std::string _items = _backup.ReturnVar("User", "Items");

	if (_username.empty() ||
			_password.empty() ||
			_categories.empty() ||
			_items.empty()){
		this->ShowError();
		return;
	}

	if (!_datFile.CreateSection(_username))
	{
		RestoreUserExists _userExists(this);
		_userExists.exec();

		if (_userExists.Replaced())
		{
			_datFile.DeleteSection(_username);
			_datFile.CreateSection(_username);
		}
		else{if (_userExists.Changed())
			{
				_username = _userExists.ReturnNewUsername();
				_datFile.CreateSection(_username);
			}
			else
				return;
		}
	}

	_iniFile.AddProperty("Users", _username, _password);

	_datFile.CreateVar(_username, "Categories", _categories);
	_datFile.CreateVar(_username, "Items", _items);

	if (_items == "empty")
		_items.clear();

	for (int i = 0; i < _items.size(); i++)
	{
		std::string temp;
		for (; (i < _items.size()) && (_items[i] != ';'); i++)
			temp += _items[i];

		std::string sectionName = _username + "/" + temp;
		_datFile.CreateSection(sectionName);

		std::string _tempCategory = _backup.ReturnVar(temp, "Category");
		std::string _tempUsername = _backup.ReturnVar(temp, "Username");
		std::string _tempPassword = _backup.ReturnVar(temp, "Password");

		if (_tempCategory.empty() ||
				_tempUsername.empty() ||
				_tempPassword.empty()){
			this->ShowError();
			return;
		}

		_datFile.CreateVar(sectionName, "Category", _tempCategory);
		_datFile.CreateVar(sectionName, "Username", _tempUsername);
		_datFile.CreateVar(sectionName, "Password", _tempPassword);
	}

	_restoredSomething = true;
	_iniFile.ApplyChanges();
	_datFile.ApplyChanges();
	QMessageBox msgB(QMessageBox::Information, "Restore successful",
					 "The restore has been successfully made.",
					 QMessageBox::Ok, this);
	msgB.exec();
	this->close();
}

void RestoreAccount::on_edtFilepath_textChanged(const QString &arg1)
{
	ui->btnRestore->setEnabled(!arg1.isEmpty());
}

bool RestoreAccount::RestoredAnAccount()
{
	return _restoredSomething;
}

void RestoreAccount::ShowError()
{
	QMessageBox msgB(QMessageBox::Critical, "Backup corrupt",
					 "The backup file you specified seems to be corrupt "
					 "or is missing data. This backup file cannot be used "
					 "to restore a profile.", QMessageBox::Ok, this);
	msgB.exec();
	return;
}
