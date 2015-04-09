#include "backupaccount.h"
#include "ui_backupaccount.h"


BackupAccount::BackupAccount(QWidget *parent, std::string username) :
	QDialog(parent),
	ui(new Ui::BackupAccount),
	_datFile(DATABASE_FILE),
	_username(username)
{
	ui->setupUi(this);
}

BackupAccount::~BackupAccount()
{
	delete ui;
}

void BackupAccount::on_btnCancel_clicked()
{
	this->close();
}

void BackupAccount::on_btnBrowse_clicked()
{
	QFileDialog saveDialog;
	std::string _filepath = saveDialog.getSaveFileName(this,"Choose where to save backup",
													   "", "Backup file (*.dat)").toStdString();
	if (_filepath.empty())
		return;

	int letter = _filepath.size() - 1;
	std::string temp;
	for (; (letter > 0) && (temp != ".dat"); letter--)
		temp = _filepath[letter] + temp;

	if (temp != ".dat")
		_filepath += ".dat";

	ui->edtFilepath->setText(_filepath.c_str());
}

void BackupAccount::on_btnBackup_clicked()
{
	std::ofstream _fileOut(ui->edtFilepath->text().toStdString().c_str());
	if (!_fileOut.is_open())
	{
		QMessageBox msgB(QMessageBox::Critical, "Couldn't create backup",
						 "An error occured while trying to create a backup "
						 "file in the location you specified. Please choose "
						 "another and make sure you have the proper permissions "
						 "to write to that location.", QMessageBox::Ok, this);
		msgB.exec();
		return;
	}
	_fileOut.close();

	cube::dataBase _backup(ui->edtFilepath->text().toStdString());
	cube::iniParser _iniFile(SETTINGS_FILE);

	QDateTime currentTime;
	currentTime.setDate(QDate::currentDate());
	currentTime.setTime(QTime::currentTime());
	_backup.AddComment("Backup made by CubePass");
	_backup.AddComment("All sensitive data is encrypted");
	_backup.AddComment("Backup made at " + currentTime.toString().toStdString());

	std::string items = _datFile.ReturnVar(_username, "Items");
	_backup.CreateSection("User");
	_backup.CreateVar("User", "Username", _username);
	_backup.CreateVar("User", "Password", _iniFile.ReturnValue("Users", _username));
	_backup.CreateVar("User", "Categories", _datFile.ReturnVar(_username, "Categories"));
	_backup.CreateVar("User", "Items", items);

	if (items == "empty")
		items.empty();

	for (int i = 0; i < items.size(); i++)
	{
		std::string temp;
		for(; (i < items.size()) && (items[i] != ';'); i++)
			temp += items[i];

		std::string _userSection = _username + "/" + temp;
		_backup.CreateSection(temp);
		_backup.CreateVar(temp, "Category", _datFile.ReturnVar(_userSection, "Category"));
		_backup.CreateVar(temp, "Username", _datFile.ReturnVar(_userSection, "Username"));
		_backup.CreateVar(temp, "Password", _datFile.ReturnVar(_userSection, "Password"));
	}
	_backup.ApplyChanges();
	std::string message = "Your backup was successfully made to ";
	message += ui->edtFilepath->text().toStdString();
	QMessageBox msgB(QMessageBox::Information, "Backup successful", message.c_str(),
					 QMessageBox::Ok, this);
	msgB.exec();
	this->close();
}

void BackupAccount::on_edtFilepath_textChanged(const QString &arg1)
{
	ui->btnBackup->setEnabled(!arg1.isEmpty());
}
