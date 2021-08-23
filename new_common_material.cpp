#include "new_common_material.h"
#include "ui_new_common_material.h"
#include "genshin_calculator.h"

new_common_material::new_common_material(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::new_common_material)
{
    ui->setupUi(this);
}

new_common_material::~new_common_material()
{
    delete ui;
}
