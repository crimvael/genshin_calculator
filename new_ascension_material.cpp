#include "new_ascension_material.h"
#include "ui_new_ascension_material.h"

new_ascension_material::new_ascension_material(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::new_ascension_material)
{
    ui->setupUi(this);
}

new_ascension_material::~new_ascension_material()
{
    delete ui;
}

void new_ascension_material::on_pushButton_clicked()
{
    accept();
}

