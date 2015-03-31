#ifndef CATEGORYMANAGER_H
#define CATEGORYMANAGER_H

#include <QDialog>
#include"stdafx.h"
#include <QListWidgetItem>

namespace Ui {
class CategoryManager;
}

class CategoryManager : public QDialog
{
    Q_OBJECT

public:
    explicit CategoryManager(std::string username);
    ~CategoryManager();

private slots:
    void on_btnAdd_clicked();

    void on_btnDelete_clicked();

    void on_lstCategories_itemClicked(QListWidgetItem *item);

private:
    Ui::CategoryManager *ui;
    std::string _username;
    cube::dataBase _datFile;
    bool _editing;
    std::vector<std::string> _categories;
};

#endif // CATEGORYMANAGER_H
