#ifndef LOGINSCREEN_H
#define LOGINSCREEN_H

#include "stdafx.h"

namespace Ui {
class LoginScreen;
}

class LoginScreen : public QDialog
{
	Q_OBJECT

public:
	explicit LoginScreen(QWidget *parent = 0);
	~LoginScreen();

	bool LoggedIn();
	std::string returnUsername();
	std::string returnPassword();

private slots:
	void on_edtUsername_textChanged(const QString &arg1);
	void on_edtPassword_textChanged(const QString &arg1);
	void on_btnLogin_clicked();
	void on_btnCreate_clicked();
	void on_btnRestore_clicked();

	void on_chckRemeber_toggled(bool checked);

private:
	Ui::LoginScreen *ui;
	cube::iniParser _iniFile;
	bool _loggedIn;
	std::string _username;
	std::string _password;
	bool _settingINI;

	void SetAllButtonsState(bool state);
};

#endif // LOGINSCREEN_H
