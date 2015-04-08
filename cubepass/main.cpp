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
		SETTINGS_FILE += "/.cubepass/settings.ini";
		DATABASE_FILE = getenv("HOME");
		DATABASE_FILE += "/.cubepass/userdata.dat";

		std::ifstream fileCheck(SETTINGS_FILE.c_str());
		if (!fileCheck.is_open())
			CreateDataFiles();
	}
	else
	{
		SETTINGS_FILE = getenv("USERPROFILE");
		SETTINGS_FILE += "\\Documents\\CubePass\\settings.ini";
		DATABASE_FILE = getenv("USERPROFILE");
		DATABASE_FILE += "\\Documents\\CubePass\\userdata.dat";

		std::ifstream fileCheck(SETTINGS_FILE.c_str());
		if (!fileCheck.is_open())
			CreateDataFiles();
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
		std::string temp = "mkdir ";
		temp += getenv("HOME");
		temp += "/.cubepass";
		std::system(temp.c_str());
	}
	else
	{
		std::string temp = "md ";
		temp += getenv("USERPROFILE");
		temp += "\\Documents\\CubePass";
		system(temp.c_str());
	}
	std::ofstream fileCreate(SETTINGS_FILE);
	fileCreate.close();
	fileCreate.open(DATABASE_FILE);
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
