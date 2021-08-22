#ifndef NEW_WEAPON_MATERIAL_H
#define NEW_WEAPON_MATERIAL_H

#include <QDialog>

namespace Ui {
class new_weapon_material;
}

class new_weapon_material : public QDialog
{
    Q_OBJECT

public:
    explicit new_weapon_material(QWidget *parent = nullptr);
    ~new_weapon_material();

private slots:
    void on_pushButton_clicked();

private:
    Ui::new_weapon_material *ui;
};

#endif // NEW_WEAPON_MATERIAL_H
