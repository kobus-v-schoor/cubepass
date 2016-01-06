#ifndef RESTOREACCOUNT_H
#define RESTOREACCOUNT_H

#include "stdafx.h"

namespace Ui {
class RestoreAccount;
}

class RestoreAccount : public QDialog
{
	Q_OBJECT

public:
	explicit RestoreAccount(QWidget *parent = 0);
	~RestoreAccount();
	bool RestoredAnAccount();

private slots:
	void on_btnBrowse_clicked();
	void on_btnCancel_clicked();
	void on_btnRestore_clicked();
	void on_edtFilepath_textChanged(const QString &arg1);

private:
	Ui::RestoreAccount *ui;
	nihdb::dataBase _datFile;
	inip::iniParser _iniFile;
	bool _restoredSomething;

	void ShowError();
};

#endif // RESTOREACCOUNT_H
