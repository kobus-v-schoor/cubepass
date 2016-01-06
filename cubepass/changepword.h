#ifndef CHANGEPWORD_H
#define CHANGEPWORD_H

#include "stdafx.h"

namespace Ui {
class ChangePword;
}

class ChangePword : public QDialog
{
	Q_OBJECT

public:
	ChangePword(QWidget *parent = 0, std::string username = "",
				std::string password = "");
	~ChangePword();
	bool PwordChanged();

private slots:
	void on_edtPassword_textChanged(const QString &arg1);
	void on_edtCPword_textChanged(const QString &arg1);
	void on_btnCancel_clicked();
	void on_btnChange_clicked();

private:
	Ui::ChangePword *ui;
	std::string _username;
	std::string _password;
	nihdb::dataBase _datFile;
	inip::iniParser _iniFile;
	bool _pwordChanged;

	void UpdateWarning();
	void Recrypt(std::string var, std::string item);
};

#endif // CHANGEPWORD_H
