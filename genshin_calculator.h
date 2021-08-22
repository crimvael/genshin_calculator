    #ifndef GENSHIN_CALCULATOR_H
    #define GENSHIN_CALCULATOR_H

    #include <QMainWindow>
    #include "add_new_character.h"
    #include "add_new_weapon.h"
    #include "new_common_material.h"
    #include "new_ascension_material.h"
    #include "new_weapon_material.h"
    #include "new_local_speciality.h"
    #include "new_talent_book.h"
    #include "new_weekly_material.h"


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

        void on_pushButton_7_clicked();

        void on_pushButton_9_clicked();

        void on_pushButton_11_clicked();

        void on_pushButton_13_clicked();

        void on_pushButton_15_clicked();

        void on_pushButton_17_clicked();

    private:
        Ui::genshin_calculator *ui;
    };
    #endif // GENSHIN_CALCULATOR_H
