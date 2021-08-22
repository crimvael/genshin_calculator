#include "genshin_calculator.h"
#include "ui_genshin_calculator.h"

genshin_calculator::genshin_calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::genshin_calculator)
{
    ui->setupUi(this);
}

genshin_calculator::~genshin_calculator()
{
    delete ui;
}

void genshin_calculator::on_pushButton_clicked()
{
    add_new_character *add_new = new add_new_character(this);
    add_new->show();
}

void genshin_calculator::on_pushButton_22_clicked()
{
    add_new_weapon *add_new = new add_new_weapon(this);
    add_new->show();
}


void genshin_calculator::on_pushButton_19_clicked()
{
    new_char_data *add_new = new new_char_data(this);
    add_new->show();
}

