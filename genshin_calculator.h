#ifndef GENSHIN_CALCULATOR_H
#define GENSHIN_CALCULATOR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class genshin_calculator; }
QT_END_NAMESPACE

class genshin_calculator : public QMainWindow
{
    Q_OBJECT

public:
    genshin_calculator(QWidget *parent = nullptr);
    ~genshin_calculator();

private:
    Ui::genshin_calculator *ui;
};
#endif // GENSHIN_CALCULATOR_H
