#ifndef NEW_CHAR_DATA_H
#define NEW_CHAR_DATA_H

#include <QDialog>

namespace Ui {
class new_char_data;
}

class new_char_data : public QDialog
{
    Q_OBJECT

public:
    explicit new_char_data(QWidget *parent = nullptr);
    ~new_char_data();

private slots:
    void on_pushButton_clicked();

private:
    Ui::new_char_data *ui;
};

#endif // NEW_CHAR_DATA_H
