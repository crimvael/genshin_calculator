#include "genshin_calculator.h"
#include "ui_genshin_calculator.h"

extern QString new_common;
QString new_common = "";

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


void genshin_calculator::on_pushButton_7_clicked()
{
    new_common_material *add_new = new new_common_material(this);
    add_new->show();
}

void genshin_calculator::get_new_common_material(QString item_name)
{
    new_common = item_name;
}


void genshin_calculator::on_pushButton_9_clicked()
{
    new_ascension_material *add_new = new new_ascension_material(this);
    add_new->show();
}


void genshin_calculator::on_pushButton_11_clicked()
{
    new_weapon_material *add_new = new new_weapon_material(this);
    add_new->show();
}


void genshin_calculator::on_pushButton_13_clicked()
{
    new_local_speciality *add_new = new new_local_speciality(this);
    add_new->show();
}


void genshin_calculator::on_pushButton_15_clicked()
{
    new_talent_book *add_new = new new_talent_book(this);
    add_new->show();
}


void genshin_calculator::on_pushButton_17_clicked()
{
    new_weekly_material *add_new = new new_weekly_material(this);
    add_new->show();
}

