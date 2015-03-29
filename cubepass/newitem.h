#ifndef NEWITEM_H
#define NEWITEM_H

#include <QDialog>

namespace Ui {
class NewItem;
}

class NewItem : public QDialog
{
    Q_OBJECT

public:
    explicit NewItem(QWidget *parent = 0);
    ~NewItem();

private:
    Ui::NewItem *ui;
};

#endif // NEWITEM_H
