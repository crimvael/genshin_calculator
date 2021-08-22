#ifndef ADD_NEW_WEAPON_H
#define ADD_NEW_WEAPON_H

#include <QDialog>

namespace Ui {
class add_new_weapon;
}

class add_new_weapon : public QDialog
{
    Q_OBJECT

public:
    explicit add_new_weapon(QWidget *parent = nullptr);
    ~add_new_weapon();

private slots:
    void on_pushButton_clicked();

private:
    Ui::add_new_weapon *ui;
};

#endif // ADD_NEW_WEAPON_H
