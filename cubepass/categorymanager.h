#ifndef CATEGORYMANAGER_H
#define CATEGORYMANAGER_H

#include <QDialog>

namespace Ui {
class CategoryManager;
}

class CategoryManager : public QDialog
{
    Q_OBJECT

public:
    explicit CategoryManager(std::string username);
    ~CategoryManager();

private:
    Ui::CategoryManager *ui;
};

#endif // CATEGORYMANAGER_H
