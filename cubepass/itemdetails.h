#ifndef ITEMDETAILS_H
#define ITEMDETAILS_H

#include "stdafx.h"

namespace Ui {
class ItemDetails;
}

class ItemDetails : public QDialog
{
	Q_OBJECT

public:
	explicit ItemDetails(QWidget* parent, std::string itemName,
						 std::string username, std::string password);
	~ItemDetails();

private slots:
	void on_chckShowPword_toggled(bool checked);
	void on_btnEdit_clicked();
	void on_btnClose_clicked();
	void on_edtItemName_textChanged(const QString &arg1);
	void on_edtUsername_textChanged(const QString &arg1);
	void on_edtPassword_textChanged(const QString &arg1);

private:
	Ui::ItemDetails *ui;
	std::string _username;
	std::string _password;
	std::string _itemName;
	nihdb::dataBase _datFile;
	bool _editing;
};

#endif // ITEMDETAILS_H
