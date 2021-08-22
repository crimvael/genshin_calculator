#ifndef NEW_WEEKLY_MATERIAL_H
#define NEW_WEEKLY_MATERIAL_H

#include <QDialog>

namespace Ui {
class new_weekly_material;
}

class new_weekly_material : public QDialog
{
    Q_OBJECT

public:
    explicit new_weekly_material(QWidget *parent = nullptr);
    ~new_weekly_material();

private slots:
    void on_pushButton_clicked();

private:
    Ui::new_weekly_material *ui;
};

#endif // NEW_WEEKLY_MATERIAL_H
