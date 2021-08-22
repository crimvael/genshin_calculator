#include "add_new_character.h"
#include "ui_add_new_character.h"

add_new_character::add_new_character(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_new_character)
{
    ui->setupUi(this);
}

add_new_character::~add_new_character()
{
    delete ui;
}

void add_new_character::on_pushButton_clicked()
{
    accept();
}

