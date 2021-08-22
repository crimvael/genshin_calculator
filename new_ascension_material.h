#ifndef NEW_ASCENSION_MATERIAL_H
#define NEW_ASCENSION_MATERIAL_H

#include <QDialog>

namespace Ui {
class new_ascension_material;
}

class new_ascension_material : public QDialog
{
    Q_OBJECT

public:
    explicit new_ascension_material(QWidget *parent = nullptr);
    ~new_ascension_material();

private slots:
    void on_pushButton_clicked();

private:
    Ui::new_ascension_material *ui;
};

#endif // NEW_ASCENSION_MATERIAL_H
