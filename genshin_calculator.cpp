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
