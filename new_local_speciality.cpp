#include "new_local_speciality.h"
#include "ui_new_local_speciality.h"

new_local_speciality::new_local_speciality(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::new_local_speciality)
{
    ui->setupUi(this);
}

new_local_speciality::~new_local_speciality()
{
    delete ui;
}

void new_local_speciality::on_pushButton_clicked()
{
    accept();
}

