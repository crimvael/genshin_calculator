#include "new_weekly_material.h"
#include "ui_new_weekly_material.h"

new_weekly_material::new_weekly_material(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::new_weekly_material)
{
    ui->setupUi(this);
}

new_weekly_material::~new_weekly_material()
{
    delete ui;
}

void new_weekly_material::on_pushButton_clicked()
{
    accept();
}

