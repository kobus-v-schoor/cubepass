#include "categorymanager.h"
#include "ui_categorymanager.h"

CategoryManager::CategoryManager(QWidget* parent, std::string username) :
	QDialog(parent),
	ui(new Ui::CategoryManager),
	_username(username),
	_datFile(DATABASE_FILE),
	_editing(false)
{
	ui->setupUi(this);

	std::string categories = _datFile.ReturnVar(_username, "Categories");
	if (categories == "empty")
		categories.clear();

	for (int i = 0; i < categories.size(); i++)
	{
		std::string temp;
		for (; (i < categories.size()) && (categories[i] != ';'); i++)
			temp += categories[i];

		ui->lstCategories->addItem(temp.c_str());
		_categories.push_back(temp);
	}

	ui->lblWarning->hide();
	ui->edtCategory->hide();
}

CategoryManager::~CategoryManager()
{
	delete ui;
}

void CategoryManager::on_btnAdd_clicked()
{
	_editing = !_editing;
	ui->btnDelete->setEnabled(!_editing);
	ui->edtCategory->setVisible(_editing);
	ui->lstCategories->setEnabled(!_editing);

	if (!_editing)
	{
		for (int i = 0; i < _categories.size(); i++)
		{
			if (_categories[i] == ui->edtCategory->text().toStdString())
			{
				ui->lblWarning->show();
				ui->edtCategory->setVisible(true);
				ui->lstCategories->setEnabled(false);
				ui->btnDelete->setEnabled(false);
				_editing = true;
				return;
			}
		}
		std::string newCategory = _datFile.ReturnVar(_username, "Categories");
		if (newCategory == "empty")
			newCategory.clear();
		newCategory += ui->edtCategory->text().toStdString() + ";";
		_datFile.ChangeVarValue(_username, "Categories", newCategory);
		_datFile.ApplyChanges();
		_categories.push_back(ui->edtCategory->text().toStdString());
		ui->lblWarning->hide();
		ui->lstCategories->addItem(ui->edtCategory->text());
		ui->edtCategory->clear();
		ui->btnDelete->setEnabled(false);
		ui->lstCategories->setCurrentRow(-1);
	}
	else
		ui->edtCategory->setFocus();
}

void CategoryManager::on_btnDelete_clicked()
{
	QMessageBox msgB(QMessageBox::Question, "Are you sure?", "Once you deleted this category "
					 "all items belonging to this category will be changed to the \"None\" category",
					 QMessageBox::Yes | QMessageBox::No, this);
	if (msgB.exec() == QMessageBox::No)
		return;

	for (std::vector<std::string>::iterator itr = _categories.begin();
		 itr != _categories.end(); itr++)
	{
		if (*itr == ui->lstCategories->currentItem()->text().toStdString())
		{
			_categories.erase(itr);
			break;
		}
	}

	std::string newCategories;

	if (_categories.empty())
		newCategories = "empty";
	else
	{
		for (int i = 0; i < _categories.size(); i++)
			newCategories += _categories[i] + ";";
	}
	_datFile.ChangeVarValue(_username, "Categories", newCategories);

	std::vector<std::string> _items;
	std::string itemNames = _datFile.ReturnVar(_username, "Items");
	for (int i = 0; i < itemNames.size(); i++)
	{
		std::string temp;
		for (; (i < itemNames.size()) && (itemNames[i] != ';'); i++)
			temp += itemNames[i];
		_items.push_back(temp);
	}

	for (int i = 0; i < _items.size(); i++)
	{
		if (_datFile.ReturnVar(_username + "/" + _items[i], "Category") ==
				ui->lstCategories->currentItem()->text().toStdString())
			_datFile.ChangeVarValue(_username + "/" + _items[i], "Category", "None");
	}
	_datFile.ApplyChanges();
	ui->lstCategories->clear();
	ui->btnDelete->setEnabled(false);

	for (int i = 0; i < _categories.size(); i++)
		ui->lstCategories->addItem(_categories[i].c_str());
}

void CategoryManager::on_lstCategories_itemClicked(QListWidgetItem *item)
{
	ui->btnDelete->setEnabled(true);
}

void CategoryManager::on_btnClose_clicked()
{
	this->close();
}
