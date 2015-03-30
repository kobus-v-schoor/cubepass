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

private slots:
    void on_edtItemName_textChanged(const QString &arg1);

    void on_edtUsername_textChanged(const QString &arg1);

    void on_edtPassword_textChanged(const QString &arg1);

    void on_edtCPassword_textChanged(const QString &arg1);

    void on_chckShowPword_toggled(bool checked);

private:
    Ui::NewItem *ui;
};

#endif // NEWITEM_H
