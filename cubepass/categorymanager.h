#ifndef CATEGORYMANAGER_H
#define CATEGORYMANAGER_H

#include"stdafx.h"


namespace Ui {
class CategoryManager;
}

class CategoryManager : public QDialog
{
	Q_OBJECT

public:
	explicit CategoryManager(QWidget* parent, std::string username);
	~CategoryManager();

private slots:
	void on_btnAdd_clicked();
	void on_btnDelete_clicked();
	void on_lstCategories_itemClicked(QListWidgetItem *item);
	void on_btnClose_clicked();

private:
	Ui::CategoryManager *ui;
	std::string _username;
	cube::dataBase _datFile;
	bool _editing;
	std::vector<std::string> _categories;
};

#endif // CATEGORYMANAGER_H
