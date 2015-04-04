#ifndef RESTOREUSEREXISTS_H
#define RESTOREUSEREXISTS_H

#include <QDialog>
#include "stdafx.h"

namespace Ui {
class RestoreUserExists;
}

class RestoreUserExists : public QDialog
{
    Q_OBJECT

public:
    explicit RestoreUserExists(QWidget *parent = 0);
    ~RestoreUserExists();
    bool Replaced();
    bool Changed();
    bool Cancelled();

private slots:
    void on_btnChange_clicked();

private:
    Ui::RestoreUserExists *ui;
    cube::dataBase _datFile;
    bool _changed;
    bool _replaced;
    bool _canceled;
};

#endif // RESTOREUSEREXISTS_H
