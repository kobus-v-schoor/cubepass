#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "stdafx.h"
#include <QListWidgetItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btnNewItem_clicked();
    void on_cmbCategory_currentIndexChanged(int index);
    void on_lstItems_itemDoubleClicked(QListWidgetItem *item);
    void on_btnManageCt_clicked();
    void on_actionLogout_triggered();
    void on_actionDelete_this_account_triggered();

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
