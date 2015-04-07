#include "helpscreen.h"
#include "ui_helpscreen.h"

HelpScreen::HelpScreen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HelpScreen)
{
    ui->setupUi(this);
}

HelpScreen::~HelpScreen()
{
    delete ui;
}
