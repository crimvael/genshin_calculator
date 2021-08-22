#ifndef GENSHIN_CALCULATOR_H
#define GENSHIN_CALCULATOR_H

#include <QMainWindow>
#include "add_new_character.h"
#include "add_new_weapon.h"
#include "new_char_data.h"

QT_BEGIN_NAMESPACE
namespace Ui { class genshin_calculator; }
QT_END_NAMESPACE

class genshin_calculator : public QMainWindow
{
    Q_OBJECT

public:
    genshin_calculator(QWidget *parent = nullptr);
    ~genshin_calculator();

private slots:

    void on_pushButton_clicked();

    void on_pushButton_22_clicked();

    void on_pushButton_19_clicked();

private:
    Ui::genshin_calculator *ui;
};
#endif // GENSHIN_CALCULATOR_H
