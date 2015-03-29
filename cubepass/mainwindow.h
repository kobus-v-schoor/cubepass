#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "stdafx.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    std::string _username;
    std::string _password;
    cube::dataBase _datFile;

    void ReLogin();
    void UpdateCategories();
    void UpdateItems();
};

#endif // MAINWINDOW_H
