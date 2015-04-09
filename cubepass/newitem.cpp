#include "newitem.h"
#include "ui_newitem.h"
#include "generatepword.h"

NewItem::NewItem(QWidget *parent, std::string username, std::string password) :
	QDialog(parent),
	ui(new Ui::NewItem),
	_username(username),
	_password(password),
	_datFile(DATABASE_FILE)
{
	ui->setupUi(this);

	std::string _categories = _datFile.ReturnVar(_username, "Categories");
	if (_categories == "empty")
		_categories.clear();

	for (int i = 0; i < _categories.size(); i++)
	{
		std::string temp;
		for (; (i < _categories.size()) && (_categories[i] != ';'); i++)
			temp += _categories[i];
		ui->cmbCategory->addItem(temp.c_str());
	}
}

NewItem::~NewItem()
{
	delete ui;
}

void NewItem::on_edtItemName_textChanged(const QString &arg1)
{
	this->updateBtnCreate();
}

void NewItem::on_edtUsername_textChanged(const QString &arg1)
{
	this->updateBtnCreate();
}

void NewItem::on_edtPassword_textChanged(const QString &arg1)
{
	this->updateBtnCreate();
}

void NewItem::on_chckShowPword_toggled(bool checked)
{
	if (checked)
		ui->edtPassword->setEchoMode(QLineEdit::Normal);
	else
		ui->edtPassword->setEchoMode(QLineEdit::Password);
}

void NewItem::on_btnCancel_clicked()
{
	this->close();
}

void NewItem::on_btnCreate_clicked()
{
	std::string _items = _datFile.ReturnVar(_username, "Items");
	if (_items == "empty")
		_items.clear();

	std::string sectionName = _username + "/" + ui->edtItemName->text().toStdString();
	if (!_datFile.CreateSection(sectionName))
	{
		QMessageBox msgB(QMessageBox::Warning, "Item exists", "This item name you specified "
						 "already exists. Please choose another.", QMessageBox::Ok, this);
		msgB.exec();
		ui->edtItemName->clear();
	}
	else
	{
		bool test;
		_items += ui->edtItemName->text().toStdString() + ";";
		_datFile.ChangeVarValue(_username, "Items", _items);

		_datFile.CreateVar(sectionName, "Category", ui->cmbCategory->currentText().toStdString());
		_datFile.CreateVar(sectionName, "Username", cube::Encryption(ui->edtUsername->text().toStdString(),
																	 _password));
		_datFile.CreateVar(sectionName, "Password", cube::Encryption(ui->edtPassword->text().toStdString(),
																	 _password));
		_datFile.ApplyChanges();
		this->close();
	}
}

void NewItem::updateBtnCreate()
{
	ui->btnCreate->setEnabled(!(ui->edtItemName->text().isEmpty() ||
								ui->edtUsername->text().isEmpty() ||
								ui->edtPassword->text().isEmpty()));
}

void NewItem::on_btnGenerate_clicked()
{
	GeneratePword generateP(this);
	generateP.exec();
	ui->edtPassword->setText(generateP.ReturnPassword());
}
