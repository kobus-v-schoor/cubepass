#include "helpscreen.h"
#include "ui_helpscreen.h"

HelpScreen::HelpScreen(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::HelpScreen),
	_iniFile(SETTINGS_FILE),
	_settingCheck(true)
{
	ui->setupUi(this);
	ui->chckShow->setChecked(_iniFile.ReturnValue("Startup", "ShowHelp") == "true");
	_settingCheck = false;
}

HelpScreen::~HelpScreen()
{
	delete ui;
}

void HelpScreen::on_tabTopics_currentChanged(int index)
{
	ui->btnPrevious->setEnabled(index != 0);
	ui->btnNext->setEnabled(index + 1 != ui->tabTopics->count());
}

void HelpScreen::on_btnPrevious_clicked()
{
	ui->tabTopics->setCurrentIndex(ui->tabTopics->currentIndex() - 1);
}

void HelpScreen::on_btnNext_clicked()
{
	ui->tabTopics->setCurrentIndex(ui->tabTopics->currentIndex() + 1);
}

void HelpScreen::on_chckShow_toggled(bool checked)
{
	if (_settingCheck)
		return;

	if (!checked)
	{
		QMessageBox(QMessageBox::Information, "Show on startup",
					"If you would like to see this screen again you access it by going "
					"to About then Help in the main window once you are logged in.",
					QMessageBox::Ok, this).exec();
	}

	inip::iniParser _iniFile(SETTINGS_FILE);
	if (checked)
		_iniFile.ChangeProperty("Startup", "ShowHelp", "true");
	else
		_iniFile.ChangeProperty("Startup", "ShowHelp", "false");

	_iniFile.ApplyChanges();
}

void HelpScreen::on_btnClose_clicked()
{
	this->close();
}
