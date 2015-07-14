#include "stdafx.h"
#include "mainwindow.h"
#include <QApplication>

#ifdef _WIN32
	#define ONWIN true
#else
	#define ONWIN false
#endif

std::string SETTINGS_FILE;
std::string DATABASE_FILE;

void CreateDataFiles();

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	if (!ONWIN)
	{
        SETTINGS_FILE = getenv("HOME");
		SETTINGS_FILE += "/.config/cubepass/settings.ini";
        DATABASE_FILE = getenv("HOME");
		DATABASE_FILE += "/.config/cubepass/userdata.dat";

		std::ifstream fileCheck(SETTINGS_FILE.c_str());
		if (!fileCheck.is_open())
			CreateDataFiles();
	}
	else
	{
		SETTINGS_FILE = getenv("APPDATA");
		SETTINGS_FILE += "\\CubePass\\settings.ini";
		DATABASE_FILE = getenv("APPDATA");
		DATABASE_FILE += "\\CubePass\\userdata.dat";

		std::ifstream fileCheck(SETTINGS_FILE.c_str());
		if (!fileCheck.is_open())
			CreateDataFiles();
	}

	cube::iniParser _iniFile(SETTINGS_FILE.c_str());

	if ((_iniFile.ReturnValue("Startup", "Version") == "2.0.0") && (VERSION != "2.0.0"))
	{
		QMessageBox msgB(QMessageBox::Critical, "Incompatible versions",
						 "Because of large changes to the "
						 "encryption your database file is incompatible with the current version of this "
						 "program. Currently there is no solution  but to downgrade to V2.0.0 and manually "
						 "store your passwords, delete the CubePass config folder (~/.cubepass and Documents"
						 "\\CubePass for *nix and Windows respectively) and re-install the newest version",
						 QMessageBox::Ok, NULL);
		msgB.exec();
		return 0;
	}

	MainWindow mainWin;
	if (!mainWin.isVisible())
		return 0;
	return a.exec();
}

void CreateDataFiles()
{
	if (!ONWIN)
	{
        std::string temp = "mkdir \"";
        temp += getenv("HOME");
        temp += "/.config/cubepass\"";
		std::system(temp.c_str());
	}
	else
	{
        std::string temp = "md \"";
		temp += getenv("APPDATA");
        temp += "\\CubePass\"";
		system(temp.c_str());
	}
	std::ofstream fileCreate(SETTINGS_FILE.c_str());
	fileCreate.close();
	fileCreate.open(DATABASE_FILE.c_str());
	fileCreate.close();

	cube::iniParser _iniFile(SETTINGS_FILE);
	cube::dataBase _datFile(DATABASE_FILE);

	_iniFile.CreateSection("Startup");
	_iniFile.AddProperty("Startup", "Version", VERSION);
	_iniFile.AddProperty("Startup", "RememberUsername", "false");
	_iniFile.AddProperty("Startup", "ShowHelp", "true");
	_iniFile.CreateSection("Users");

	_datFile.AddComment("CubePass database");
	_datFile.AddComment("This database stores all the data for CubePass");
	_datFile.AddComment("ALL SENSITIVE DATA IS ENCRYPTED");
	_datFile.AddComment("");

	_iniFile.ApplyChanges();
	_datFile.ApplyChanges();
	return;
}
