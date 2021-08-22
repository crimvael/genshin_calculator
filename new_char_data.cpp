#include "new_char_data.h"
#include "ui_new_char_data.h"

new_char_data::new_char_data(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::new_char_data)
{
    ui->setupUi(this);
}

new_char_data::~new_char_data()
{
    delete ui;
}

void new_char_data::on_pushButton_clicked()
{
    accept();
}

