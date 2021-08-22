#ifndef NEW_TALENT_BOOK_H
#define NEW_TALENT_BOOK_H

#include <QDialog>

namespace Ui {
class new_talent_book;
}

class new_talent_book : public QDialog
{
    Q_OBJECT

public:
    explicit new_talent_book(QWidget *parent = nullptr);
    ~new_talent_book();

private slots:
    void on_pushButton_clicked();

private:
    Ui::new_talent_book *ui;
};

#endif // NEW_TALENT_BOOK_H
