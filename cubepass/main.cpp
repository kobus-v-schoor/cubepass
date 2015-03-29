#include "stdafx.h"
#include "mainwindow.h"
#include <QApplication>

#ifdef _WIN32
    #define ONWIN true
#else
    #define ONWIN false
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    cube::iniParser _iniFile(SETTINGS_FILE);
    cube::dataBase _datFile(DAT_FILE);

    if (!_iniFile.IsParsed())
    {
        QMessageBox msgB(QMessageBox::Critical, "Settings corrupt", "The \"settings.ini\" file "
                    "seems to be corrupt. Please make sure htis program has read and write access "
                    "to this file. Re-installing will fix his problem if the file was damaged.",
                    QMessageBox::Ok);
        msgB.exec();
        return 0;
    }

    if (!_datFile.IsParsed())
    {
        QMessageBox msgB(QMessageBox::Critical, "User data corrupt", "The \"userdata.dat\" file "
                    "seems to be corrupt. Please make sure htis program has read and write access "
                    "to this file. Re-installing will fix his problem if the file was damaged.",
                    QMessageBox::Ok);
        msgB.exec();
        return 0;
    }

    if (ONWIN)
    {
        QMessageBox msgB(QMessageBox::Information, "Permissions needed", "I detected that your running Windows. "
                         "Because of this, especially if you're runnig Win 8, you need to run this program "
                         "with admin rights. If not, this program will not be able to save any of its data. "
                         "To do this, simply right-click on the shortcut and click \"Run as administrator\".",
                         QMessageBox::Ok);
        msgB.exec();
        _iniFile.ChangeProperty("Startup", "FirstStart", "false");
        _iniFile.ApplyChanges();
        return 0;
    }

    MainWindow mainWin;
    if (!mainWin.isVisible())
        return 0;
    return a.exec();
}
