#include "new_talent_book.h"
#include "ui_new_talent_book.h"

new_talent_book::new_talent_book(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::new_talent_book)
{
    ui->setupUi(this);
}

new_talent_book::~new_talent_book()
{
    delete ui;
}

void new_talent_book::on_pushButton_clicked()
{
    accept();
}

