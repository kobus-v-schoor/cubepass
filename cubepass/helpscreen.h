#ifndef HELPSCREEN_H
#define HELPSCREEN_H

#include <QDialog>
#include "stdafx.h"

namespace Ui {
class HelpScreen;
}

class HelpScreen : public QDialog
{
	Q_OBJECT

public:
	explicit HelpScreen(QWidget *parent = 0);
	~HelpScreen();

private slots:
	void on_tabTopics_currentChanged(int index);
	void on_btnPrevious_clicked();
	void on_btnNext_clicked();
	void on_chckShow_toggled(bool checked);

private:
	Ui::HelpScreen *ui;
	cube::iniParser _iniFile;
	bool _settingCheck;
};

#endif // HELPSCREEN_H
