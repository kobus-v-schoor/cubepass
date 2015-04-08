#include "generatepword.h"
#include "ui_generatepword.h"

GeneratePword::GeneratePword(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::GeneratePword)
{
	ui->setupUi(this);
}

GeneratePword::~GeneratePword()
{
	delete ui;
}

void GeneratePword::on_edtPassword_textChanged(const QString &arg1)
{
	ui->btnUsePword->setEnabled(!arg1.isEmpty());
}

void GeneratePword::on_btnCancel_clicked()
{
	ui->edtPassword->clear();
	this->close();
}

QString GeneratePword::ReturnPassword()
{
	return ui->edtPassword->text();
}

void GeneratePword::on_btnUsePword_clicked()
{
	this->close();
}

void GeneratePword::on_btnGenerate_clicked()
{
	std::string password;
	enum Conditions { Lowercase, Uppercase, Special, Numbers };
	std::vector<Conditions> _conditions;

	if (ui->chckLowercase->isChecked())
		_conditions.push_back(Lowercase);

	if (ui->chckUppercase->isChecked())
		_conditions.push_back(Uppercase);

	if (ui->chckSpecial->isChecked())
		_conditions.push_back(Special);

	if (ui->chckNumbers->isChecked())
		_conditions.push_back(Numbers);

	if (_conditions.empty()){
		ui->chckLowercase->setChecked(true);
		_conditions.push_back(Lowercase);
	}


	srand(clock());

	for (int i = 0; i < ui->spnLength->value(); i++)
	{
		Conditions letterType = _conditions[rand () % _conditions.size()];
		int charNum;

		switch (letterType) {
		case Lowercase : {charNum = rand() % 26 + 97; break;}
		case Uppercase : {charNum = rand() % 26 + 65; break;}
		case Special : {charNum = rand() % 32 + 33; break;}
		case Numbers : {charNum = rand() % 10 + 48; break;}
		}

		password += char(charNum);
	}
	ui->edtPassword->setText(password.c_str());
}
