#include "add_new_weapon.h"
#include "ui_add_new_weapon.h"

add_new_weapon::add_new_weapon(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_new_weapon)
{
    ui->setupUi(this);
}

add_new_weapon::~add_new_weapon()
{
    delete ui;
}

void add_new_weapon::on_pushButton_clicked()
{
    accept();
}

