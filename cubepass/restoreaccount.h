#ifndef RESTOREACCOUNT_H
#define RESTOREACCOUNT_H

#include <QDialog>

namespace Ui {
class RestoreAccount;
}

class RestoreAccount : public QDialog
{
    Q_OBJECT

public:
    explicit RestoreAccount(QWidget *parent = 0);
    ~RestoreAccount();

private:
    Ui::RestoreAccount *ui;
};

#endif // RESTOREACCOUNT_H
