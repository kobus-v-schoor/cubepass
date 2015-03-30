#include "itemdetails.h"
#include "ui_itemdetails.h"

ItemDetails::ItemDetails(std::string itemName, std::string username, std::string password) :
    ui(new Ui::ItemDetails),
    _itemName(itemName),
    _username(username),
    _password(password),
    _datFile(DAT_FILE),
    _editing(false)
{
    ui->setupUi(this);

    std::string sectionName = _username + "/" + _itemName;
    ui->edtItemName->setText(_itemName.c_str());
    ui->edtUsername->setText(cube::Decryption(_datFile.ReturnVar(sectionName, "Username"), _password).c_str());
    ui->edtPassword->setText(cube::Decryption(_datFile.ReturnVar(sectionName, "Password"), _password).c_str());
    std::string _categories = _datFile.ReturnVar(_username, "Categories");
    if (_categories == "empty")
        _categories.empty();

    ui->cmbCategory->addItem("None");
    for (int i = 0; i < _categories.size(); i++)
    {
        std::string temp;
        for (; (i < _categories.size()) && (_categories[i] != ';'); i++)
            temp += _categories[i];

        ui->cmbCategory->addItem(temp.c_str());
    }
    ui->cmbCategory->setCurrentText(_datFile.ReturnVar(sectionName, "Category").c_str());
}

ItemDetails::~ItemDetails()
{
    delete ui;
}

void ItemDetails::on_chckShowPword_toggled(bool checked)
{
    if (checked)
        ui->edtPassword->setEchoMode(QLineEdit::Normal);
    else
        ui->edtPassword->setEchoMode(QLineEdit::Password);
}

void ItemDetails::on_btnEdit_clicked()
{
    _editing = !_editing;

    if (_editing)
    {
        ui->edtItemName->setReadOnly(false);
        ui->edtUsername->setReadOnly(false);
        ui->edtPassword->setReadOnly(false);
        ui->cmbCategory->setEnabled(true);
        ui->btnEdit->setText("Save changes");
        ui->btnDone->setText("Delete");

        return;
    }

    bool _succeeded;
    bool nameUnchanged = (ui->edtItemName->text().toStdString() == _itemName);

    if (!nameUnchanged)
        _succeeded = _datFile.CreateSection(_username + "/" + ui->edtItemName->text().toStdString());
    else
        _succeeded = true;

    if (!_succeeded)
    {
        QMessageBox msgB(QMessageBox::Warning, "Item exists", "An item with the name you specified "
                         "already exists. Please choose another.", QMessageBox::Ok);
        msgB.exec();
        _editing = true;
        return;
    }

    if (!nameUnchanged)
    {
        _datFile.DeleteSection(_username + "/" + _itemName);

        std::string items = _datFile.ReturnVar(_username, "Items");
        std::string newItems;
        for (int i = 0; i < items.size(); i++)
        {
            std::string temp;
            for (; (i < items.size()) && (items[i] != ';'); i++)
                temp += items[i];

            if (temp != _itemName)
                newItems += temp + ";";
        }
         newItems += ui->edtItemName->text().toStdString() + ";";
        _datFile.ChangeVarValue(_username, "Items", newItems);
    }
    std::string sectionName = _username + "/" + ui->edtItemName->text().toStdString();

    if (!nameUnchanged)
    {
        _datFile.CreateVar(sectionName, "ItemName");
        _datFile.CreateVar(sectionName, "Category");
        _datFile.CreateVar(sectionName, "Username");
        _datFile.CreateVar(sectionName, "Password");
    }

    _datFile.ChangeVarValue(sectionName, "Category", ui->cmbCategory->currentText().toStdString());
    _datFile.ChangeVarValue(sectionName, "Username", cube::Encryption(ui->edtUsername->text().toStdString(),
                                                                      _password));
    _datFile.ChangeVarValue(sectionName, "Password", cube::Encryption(ui->edtPassword->text().toStdString(),
                                                                      _password));
    _datFile.ApplyChanges();

    ui->edtItemName->setReadOnly(true);
    ui->edtUsername->setReadOnly(true);
    ui->edtPassword->setReadOnly(true);
    ui->cmbCategory->setEnabled(false);
    ui->btnEdit->setText("Edit");
    ui->btnDone->setText("Done");
}

void ItemDetails::on_btnDone_clicked()
{
    if (!_editing)
        this->close();
    else
    {
        QMessageBox msgB(QMessageBox::Question, "Are you sure?", "If you delete this item "
                         "you won't be able to undo your action.", QMessageBox::Yes | QMessageBox::No);
        if (msgB.exec() == QMessageBox::Yes)
        {
            _datFile.DeleteSection(_username + "/" + _itemName);

            std::string items = _datFile.ReturnVar(_username, "Items");
            std::string newItems;
            for (int i = 0; i < items.size(); i++)
            {
                std::string temp;
                for (; (i < items.size()) && (items[i] != ';'); i++)
                    temp += items[i];

                if (temp != _itemName)
                    newItems += temp + ";";
            }
            if (newItems.empty())
                newItems = "empty";

            _datFile.ChangeVarValue(_username, "Items", newItems);
            _datFile.ApplyChanges();
            this->close();
        }
    }
}
