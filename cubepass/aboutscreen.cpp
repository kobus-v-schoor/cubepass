#include "aboutscreen.h"
#include "ui_aboutscreen.h"
#include <QDesktopServices>
#include <QUrl>

AboutScreen::AboutScreen(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::AboutScreen)
{
	ui->setupUi(this);
}

AboutScreen::~AboutScreen()
{
	delete ui;
}

void AboutScreen::on_btnDonate_clicked()
{
	ui->btnDonate->setText("Thank you very much :D");
	QString donateUrl("https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=GHDMPQVJS8832");
	QDesktopServices::openUrl(QUrl(donateUrl));
}
