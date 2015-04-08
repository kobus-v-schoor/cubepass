#ifndef DELETEACCOUNT_H
#define DELETEACCOUNT_H

#include <QDialog>
#include "stdafx.h"

namespace Ui {
class DeleteAccount;
}

class DeleteAccount : public QDialog
{
	Q_OBJECT

public:
	explicit DeleteAccount(QWidget* parent, std::string username);
	~DeleteAccount();
	bool DeletedAccount();

private slots:
	void on_edtConfirm_textChanged(const QString &arg1);
	void on_btnCancel_clicked();
	void on_btnDelete_clicked();

private:
	Ui::DeleteAccount *ui;
	std::string _username;
	cube::dataBase _datFile;
	cube::iniParser _iniFile;
	bool _deletedAccount;
};

#endif // DELETEACCOUNT_H
