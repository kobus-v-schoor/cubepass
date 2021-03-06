#ifndef CREATEUSER_H
#define CREATEUSER_H

#include "stdafx.h"

namespace Ui {
class CreateUser;
}

class CreateUser : public QDialog
{
	Q_OBJECT

public:
	explicit CreateUser(QWidget *parent = 0);
	~CreateUser();

private slots:
	void on_btnCancel_clicked();
	void on_btnCreate_clicked();
	void on_edtPassword_textChanged(const QString &arg1);
	void on_edtCPword_textChanged(const QString &arg1);
	void on_edtUsername_textChanged(const QString &arg1);

private:
	Ui::CreateUser *ui;
	inip::iniParser _iniFile;
	nihdb::dataBase _datFile;
};

#endif // CREATEUSER_H
