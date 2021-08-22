#ifndef NEW_COMMON_MATERIAL_H
#define NEW_COMMON_MATERIAL_H

#include <QDialog>

namespace Ui {
class new_common_material;
}

class new_common_material : public QDialog
{
    Q_OBJECT

public:
    explicit new_common_material(QWidget *parent = nullptr);
    ~new_common_material();

private slots:
    void on_pushButton_clicked();

private:
    Ui::new_common_material *ui;
};

#endif // NEW_COMMON_MATERIAL_H
