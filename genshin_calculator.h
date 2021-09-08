    #ifndef GENSHIN_CALCULATOR_H
    #define GENSHIN_CALCULATOR_H

    #include <QMainWindow>
    #include "QTableWidget"
    #include "QJsonObject"


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

        void refresh_items();

        void add_new_material(int);

        void remove_material(int);

        void on_pushButton_7_clicked();

        void on_pushButton_8_clicked();

        void on_pushButton_9_clicked();

        void on_pushButton_10_clicked();

        void on_pushButton_13_clicked();

        void on_pushButton_14_clicked();

        void on_pushButton_15_clicked();

        void on_pushButton_16_clicked();

        void on_pushButton_17_clicked();

        void on_pushButton_18_clicked();

        void on_pushButton_11_clicked();

        void on_pushButton_12_clicked();

        void on_pushButton_4_clicked();

        void on_pushButton_3_clicked();

        void on_listWidget_7_itemSelectionChanged();

        void update_training_list();

        void update_char_list();

        void update_weapon_list();

        void update_weapon_training_list();

        void on_pushButton_19_clicked();

        void on_pushButton_24_clicked();

        void on_pushButton_23_clicked();

        void on_pushButton_clicked();

        void calculate();

        void ascension(QString);

        void talent(QString);

        void resize_layouts();

        void on_pushButton_20_clicked();

        void on_pushButton_6_clicked();

        void on_pushButton_22_clicked();

        void calculate_weapons(QString);

        void on_listWidget_8_itemSelectionChanged();

        void on_pushButton_5_clicked();

    private:
        Ui::genshin_calculator *ui;
    };
    #endif // GENSHIN_CALCULATOR_H
