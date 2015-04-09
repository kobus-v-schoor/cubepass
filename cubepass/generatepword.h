#ifndef GENERATEPWORD_H
#define GENERATEPWORD_H

#include "stdafx.h"

namespace Ui {
class GeneratePword;
}

class GeneratePword : public QDialog
{
	Q_OBJECT

public:
	explicit GeneratePword(QWidget *parent = 0);
	~GeneratePword();
	QString ReturnPassword();

private slots:
	void on_edtPassword_textChanged(const QString &arg1);
	void on_btnCancel_clicked();

	void on_btnUsePword_clicked();

	void on_btnGenerate_clicked();

private:
	Ui::GeneratePword *ui;
};

#endif // GENERATEPWORD_H
