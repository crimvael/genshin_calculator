#include "new_weapon_material.h"
#include "ui_new_weapon_material.h"

new_weapon_material::new_weapon_material(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::new_weapon_material)
{
    ui->setupUi(this);
}

new_weapon_material::~new_weapon_material()
{
    delete ui;
}

void new_weapon_material::on_pushButton_clicked()
{
    accept();
}

