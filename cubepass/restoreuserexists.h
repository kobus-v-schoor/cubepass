#ifndef RESTOREUSEREXISTS_H
#define RESTOREUSEREXISTS_H

#include "stdafx.h"

namespace Ui {
class RestoreUserExists;
}

class RestoreUserExists : public QDialog
{
	Q_OBJECT

public:
	explicit RestoreUserExists(QWidget *parent = 0);
	~RestoreUserExists();
	bool Replaced();
	bool Changed();
	std::string ReturnNewUsername();

private slots:
	void on_btnChange_clicked();
	void on_edtNewUser_textChanged(const QString &arg1);
	void on_btnReplace_clicked();
	void on_btnCancel_clicked();

private:
	Ui::RestoreUserExists *ui;
	cube::dataBase _datFile;
	bool _changed;
	bool _replace;
	std::string _newUsername;
};

#endif // RESTOREUSEREXISTS_H
