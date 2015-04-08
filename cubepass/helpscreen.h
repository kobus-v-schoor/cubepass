#ifndef HELPSCREEN_H
#define HELPSCREEN_H

#include <QDialog>

namespace Ui {
class HelpScreen;
}

class HelpScreen : public QDialog
{
	Q_OBJECT

public:
	explicit HelpScreen(QWidget *parent = 0);
	~HelpScreen();

private:
	Ui::HelpScreen *ui;
};

#endif // HELPSCREEN_H
