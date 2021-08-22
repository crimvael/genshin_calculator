#ifndef NEW_LOCAL_SPECIALITY_H
#define NEW_LOCAL_SPECIALITY_H

#include <QDialog>

namespace Ui {
class new_local_speciality;
}

class new_local_speciality : public QDialog
{
    Q_OBJECT

public:
    explicit new_local_speciality(QWidget *parent = nullptr);
    ~new_local_speciality();

private slots:
    void on_pushButton_clicked();

private:
    Ui::new_local_speciality *ui;
};

#endif // NEW_LOCAL_SPECIALITY_H
