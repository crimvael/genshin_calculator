#ifndef ADD_NEW_CHARACTER_H
#define ADD_NEW_CHARACTER_H

#include <QDialog>

namespace Ui {
class add_new_character;
}

class add_new_character : public QDialog
{
    Q_OBJECT

public:
    explicit add_new_character(QWidget *parent = nullptr);
    ~add_new_character();

private slots:
    void on_pushButton_clicked();

private:
    Ui::add_new_character *ui;
};

#endif // ADD_NEW_CHARACTER_H
