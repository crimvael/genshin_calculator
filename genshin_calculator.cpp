#include "genshin_calculator.h"
#include "ui_genshin_calculator.h"
#include "QJsonDocument"
#include "QJsonObject"
#include "QJsonArray"
#include "QFile"

extern QString filepath;
QString filepath = "C:/Users/Secernato/Documents/Qt projects/genshin_calculator/database.json";
//QString filepath = "C:/Users/Oscar/Desktop/genshin_calculator/database.json"

genshin_calculator::genshin_calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::genshin_calculator)
{
    ui->setupUi(this);
    refresh_items();

    QString val;
    QFile file;
    file.setFileName(filepath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject jsonObject = jsonResponse.object();
    QJsonArray jsonArray = jsonObject["common_materials"].toArray();
    QJsonArray jsonArray_2 = jsonObject["talent_materials"].toArray();

    for (int i=0; i<jsonArray.size(); i++) {
        ui->tableWidget_8->insertRow(i);
        ui->tableWidget_9->insertRow(i);
        ui->tableWidget_10->insertRow(i);
        ui->tableWidget_12->insertRow(i);

        ui->tableWidget_8->setItem(i, 0, new QTableWidgetItem(jsonArray_2[i].toString()));
        ui->tableWidget_9->setItem(i, 0, new QTableWidgetItem(jsonArray[i].toString()));
        ui->tableWidget_10->setItem(i, 0, new QTableWidgetItem(jsonArray[i].toString()));
        ui->tableWidget_12->setItem(i, 0, new QTableWidgetItem(jsonArray[i].toString()));
    }

    update_char_list();
    update_training_list();
    update_weapon_list();
    update_weapon_training_list();
    calculate();

    resize_layouts();

}

genshin_calculator::~genshin_calculator()
{
    delete ui;
}

void genshin_calculator::refresh_items(){

    QString val;
    QFile file;
    file.setFileName(filepath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject jsonObject = jsonResponse.object();
    QJsonArray jsonArray = jsonObject["common_materials"].toArray();
    QJsonArray jsonArray_2 = jsonObject["ascension_materials"].toArray();
    QJsonArray jsonArray_3 = jsonObject["elite_materials"].toArray();
    QJsonArray jsonArray_4 = jsonObject["local_materials"].toArray();
    QJsonArray jsonArray_5 = jsonObject["talent_materials"].toArray();
    QJsonArray jsonArray_6 = jsonObject["weekly_materials"].toArray();
    QJsonArray jsonArray_7 = jsonObject["weapon_materials"].toArray();
    QJsonObject tmp;
    ui->listWidget->clear();
    ui->listWidget_2->clear();
    ui->listWidget_3->clear();
    ui->listWidget_4->clear();
    ui->listWidget_5->clear();
    ui->listWidget_6->clear();
    ui->listWidget_9->clear();
    for (int i = 0; i<jsonArray.size(); i++){
        ui->listWidget->addItem(jsonArray[i].toString());
        ui->comboBox_3->addItem(jsonArray[i].toString());
        ui->comboBox_9->addItem(jsonArray[i].toString());
    }
    for (int i = 0; i<jsonArray_2.size(); i++){
        ui->listWidget_2->addItem(jsonArray_2[i].toString());
        ui->comboBox_4->addItem(jsonArray_2[i].toString());
    }
    for (int i = 0; i<jsonArray_3.size(); i++){
        ui->listWidget_3->addItem(jsonArray_3[i].toString());
        ui->comboBox_10->addItem(jsonArray_3[i].toString());
    }
    for (int i = 0; i<jsonArray_4.size(); i++){
        ui->listWidget_4->addItem(jsonArray_4[i].toString());
        ui->comboBox_5->addItem(jsonArray_4[i].toString());
    }
    for (int i = 0; i<jsonArray_5.size(); i++){
        ui->listWidget_5->addItem(jsonArray_5[i].toString());
        ui->comboBox_6->addItem(jsonArray_5[i].toString());
    }
    for (int i = 0; i<jsonArray_6.size(); i++){
        ui->listWidget_6->addItem(jsonArray_6[i].toString());
        ui->comboBox_7->addItem(jsonArray_6[i].toString());
    }
    for (int i = 0; i<jsonArray_7.size(); i++){
        ui->listWidget_9->addItem(jsonArray_7[i].toString());
        ui->comboBox_12->addItem(jsonArray_7[i].toString());
    }
}

void genshin_calculator::calculate(){

    ui->tableWidget_5->setRowCount(0);
    ui->tableWidget_6->setRowCount(0);
    ui->tableWidget_14->setRowCount(0);
    for (int i=0; i<ui->tableWidget_7->rowCount(); i++) {
        for (int j=0; j<ui->tableWidget_7->columnCount(); j++) {
            ui->tableWidget_7->setItem(i, j, nullptr);
        }
    }
    for (int i=0; i<ui->tableWidget_9->rowCount(); i++) {
        for (int j=1; j<ui->tableWidget_9->columnCount(); j++) {
            ui->tableWidget_9->setItem(i, j, nullptr);
        }
    }
    for (int i=0; i<ui->tableWidget_8->rowCount(); i++) {
        for (int j=1; j<ui->tableWidget_8->columnCount(); j++) {
            ui->tableWidget_8->setItem(i, j, nullptr);
        }
    }
    for (int i=0; i<ui->tableWidget_10->rowCount(); i++) {
        for (int j=1; j<ui->tableWidget_10->columnCount(); j++) {
            ui->tableWidget_10->setItem(i, j, nullptr);
        }
    }

    QString val;
    QFile file;
    file.setFileName(filepath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();

    ascension(val);
    talent(val);
    calculate_weapons(val);

    for (int i=0; i<ui->tableWidget_12->rowCount(); i++) {
        for (int j=1; j<ui->tableWidget_12->columnCount(); j++) {
            int a = 0, b = 0;
            if (ui->tableWidget_9->item(i, j) != nullptr)
                a += ui->tableWidget_9->item(i, j)->text().toInt();
            if (ui->tableWidget_10->item(i, j) != nullptr)
                b += ui->tableWidget_10->item(i, j)->text().toInt();
            if (a+b > 0){
                QTableWidgetItem *item =  new QTableWidgetItem(QString::number(a+b));
                item->setTextAlignment(Qt::AlignCenter);
                ui->tableWidget_12->setItem(i, j, item);
            }
        }
    }

    resize_layouts();
}

void genshin_calculator::ascension(QString val){

    QJsonDocument jsonResponse = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject jsonObject = jsonResponse.object();
    QJsonArray jsonArray = jsonObject["training"].toArray();
    QJsonArray jsonArray_2 = jsonObject["characters"].toArray();

    QJsonObject tmp;
    int quantity[] = {0,0,0,0,0,0,0};
    int needed[] = {7,29,29,43,60,81,171};

    int ascen_mora = 0;
    for (int i=0; i<jsonArray.size(); i++) {
        tmp = jsonArray.at(i).toObject();
        if (tmp["Check"].toBool()){
            int local_needed = 0;
            int ascen_needed = 0;
            int stones_needed[] = {0,0,0,0};
            int common_needed[] = {0,0,0};
            int phase = tmp["Phase"].toString().toInt();
            int curr = tmp["Current lvl"].toString().toInt();
            int targ = tmp["Target lvl"].toString().toInt();
            if (curr < 20 && curr < targ)
                quantity[0]++;
            if (curr < 40 && curr < targ)
                quantity[1]++;
            if (curr < 50 && curr < targ)
                quantity[2]++;
            if (curr < 60 && curr < targ)
                quantity[3]++;
            if (curr < 70 && curr < targ)
                quantity[4]++;
            if (curr < 80 && curr < targ)
                quantity[5]++;
            if (curr < 90 && curr < targ)
                quantity[6]++;

            if (phase < 1){
                local_needed+=3;
                stones_needed[3] +=1;
                common_needed[2] +=3;
                ascen_mora += 20000;
            }
            if (phase < 2){
                local_needed+=10;
                ascen_needed+=2;
                stones_needed[2] +=3;
                common_needed[2] +=15;
                ascen_mora += 40000;
            }
            if (phase < 3){
                local_needed+=20;
                ascen_needed+=4;
                stones_needed[2] +=6;
                common_needed[1] +=12;
                ascen_mora += 60000;
            }
            if (phase < 4){
                local_needed+=30;
                ascen_needed+=8;
                stones_needed[1] +=3;
                ascen_mora += 80000;
            }
            if (phase < 5){
                local_needed+=45;
                ascen_needed+=12;
                stones_needed[1] +=6;
                common_needed[0] +=12;
                ascen_mora += 100000;
            }
            if (phase < 6){
                local_needed+=60;
                ascen_needed+=20;
                stones_needed[0] +=6;
                common_needed[0] +=24;
                ascen_mora += 120000;
            }

            if (local_needed > 0){
                for (int i=0; i<jsonArray_2.size(); i++) {
                    QJsonObject tmp2 = jsonArray_2.at(i).toObject();
                    bool already_exist = false;
                    int row = 0;
                    if (tmp["Name"].toString() == tmp2["Name"].toString()){
                        for (int i=0; i<ui->tableWidget_5->rowCount(); i++)
                            if (ui->tableWidget_5->item(i, 0)->text() == tmp2["Local speciality"].toString()){
                                already_exist = true;
                                row = i;
                            }

                        if (already_exist){
                            local_needed += ui->tableWidget_5->item(row, 1)->text().toInt();
                            QTableWidgetItem *item =  new QTableWidgetItem(QString::number(local_needed));
                            item->setTextAlignment(Qt::AlignCenter);
                            ui->tableWidget_5->setItem(ui->tableWidget_5->rowCount()-1, 1, item);
                        }
                        else{
                            ui->tableWidget_5->insertRow(ui->tableWidget_5->rowCount());
                            QTableWidgetItem *item =  new QTableWidgetItem(tmp2["Local speciality"].toString());
                            ui->tableWidget_5->setItem(ui->tableWidget_5->rowCount()-1, 0, item);
                            QTableWidgetItem *item_2 =  new QTableWidgetItem(QString::number(local_needed));
                            item_2->setTextAlignment(Qt::AlignCenter);
                            ui->tableWidget_5->setItem(ui->tableWidget_5->rowCount()-1, 1, item_2);
                        }
                    }
                }
            }

            if (ascen_needed > 0){
                for (int i=0; i<jsonArray_2.size(); i++) {
                    QJsonObject tmp2 = jsonArray_2.at(i).toObject();
                    bool already_exist = false;
                    int row = 0;
                    if (tmp["Name"].toString() == tmp2["Name"].toString()){

                        for (int i=0; i<ui->tableWidget_6->rowCount(); i++)
                            if (ui->tableWidget_6->item(i, 0)->text() == tmp2["Ascension material"].toString()){
                                already_exist = true;
                                row = i;
                            }

                        if (already_exist){
                            ascen_needed += ui->tableWidget_6->item(row, 1)->text().toInt();
                            QTableWidgetItem *item =  new QTableWidgetItem(QString::number(ascen_needed));
                            item->setTextAlignment(Qt::AlignCenter);
                            ui->tableWidget_6->setItem(row, 1, item);
                        }
                        else{
                            ui->tableWidget_6->insertRow(ui->tableWidget_6->rowCount());
                            QTableWidgetItem *item =  new QTableWidgetItem(tmp2["Ascension material"].toString());
                            ui->tableWidget_6->setItem(ui->tableWidget_6->rowCount()-1, 0, item);
                            QTableWidgetItem *item_2 =  new QTableWidgetItem(QString::number(ascen_needed));
                            item_2->setTextAlignment(Qt::AlignCenter);
                            ui->tableWidget_6->setItem(ui->tableWidget_6->rowCount()-1, 1, item_2);
                        }
                    }
                }
            }

            if (phase < 6){
                for (int i=0; i<jsonArray_2.size(); i++) {
                    QJsonObject tmp2 = jsonArray_2.at(i).toObject();
                    int row = 0;
                    if (tmp["Name"].toString() == tmp2["Name"].toString()){
                        for (int i=0; i<ui->tableWidget_7->rowCount(); i++)
                            if (ui->tableWidget_7->verticalHeaderItem(i)->text() == tmp2["Vision"].toString())
                                row = i;

                        if (ui->tableWidget_7->item(row, 3) != nullptr)
                            stones_needed[3] += ui->tableWidget_7->item(row, 3)->text().toInt();
                        if (ui->tableWidget_7->item(row, 2) != nullptr)
                            stones_needed[2] += ui->tableWidget_7->item(row, 2)->text().toInt();
                        if (ui->tableWidget_7->item(row, 1) != nullptr)
                            stones_needed[1] += ui->tableWidget_7->item(row, 1)->text().toInt();
                        if (ui->tableWidget_7->item(row, 0) != nullptr)
                            stones_needed[0] += ui->tableWidget_7->item(row, 0)->text().toInt();
                        QTableWidgetItem *item =  new QTableWidgetItem(QString::number(stones_needed[3]));
                        QTableWidgetItem *item_2 =  new QTableWidgetItem(QString::number(stones_needed[2]));
                        QTableWidgetItem *item_3 =  new QTableWidgetItem(QString::number(stones_needed[1]));
                        QTableWidgetItem *item_4 =  new QTableWidgetItem(QString::number(stones_needed[0]));
                        item->setTextAlignment(Qt::AlignCenter);
                        item_2->setTextAlignment(Qt::AlignCenter);
                        item_3->setTextAlignment(Qt::AlignCenter);
                        item_4->setTextAlignment(Qt::AlignCenter);
                        if (stones_needed[3] > 0)
                            ui->tableWidget_7->setItem(row, 3, item);
                        if (stones_needed[2] > 0)
                            ui->tableWidget_7->setItem(row, 2, item_2);
                        if (stones_needed[1] > 0)
                            ui->tableWidget_7->setItem(row, 1, item_3);
                        if (stones_needed[0] > 0)
                            ui->tableWidget_7->setItem(row, 0, item_4);
                    }
                }
            }

            if (phase < 6){
                for (int i=0; i<jsonArray_2.size(); i++) {
                    QJsonObject tmp2 = jsonArray_2.at(i).toObject();
                    int row = 0;
                    if (tmp["Name"].toString() == tmp2["Name"].toString()){
                        for (int i=0; i<ui->tableWidget_9->rowCount(); i++)
                            if (ui->tableWidget_9->item(i, 0)->text() == tmp2["Common material"].toString())
                                row = i;

                        if (ui->tableWidget_9->item(row, 3) != nullptr)
                            common_needed[2] += ui->tableWidget_9->item(row, 3)->text().toInt();
                        if (ui->tableWidget_9->item(row, 2) != nullptr)
                            common_needed[1] += ui->tableWidget_9->item(row, 2)->text().toInt();
                        if (ui->tableWidget_9->item(row, 1) != nullptr)
                            common_needed[0] += ui->tableWidget_9->item(row, 1)->text().toInt();
                        QTableWidgetItem *item_2 =  new QTableWidgetItem(QString::number(common_needed[2]));
                        QTableWidgetItem *item_3 =  new QTableWidgetItem(QString::number(common_needed[1]));
                        QTableWidgetItem *item_4 =  new QTableWidgetItem(QString::number(common_needed[0]));
                        item_2->setTextAlignment(Qt::AlignCenter);
                        item_3->setTextAlignment(Qt::AlignCenter);
                        item_4->setTextAlignment(Qt::AlignCenter);
                        if (common_needed[2] > 0)
                            ui->tableWidget_9->setItem(row, 3, item_2);
                        if (common_needed[1] > 0)
                            ui->tableWidget_9->setItem(row, 2, item_3);
                        if (common_needed[0] > 0)
                            ui->tableWidget_9->setItem(row, 1, item_4);
                    }
                }
            }
        }
    }

    int total_wit = 0;
    int total_mora = 0;
    for (int i=0; i < 7; i++ ) {
        // quantity
        QTableWidgetItem *item =  new QTableWidgetItem(QString::number(quantity[i]));
        item->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget_4->setItem(i, 1, item);
        // needed
        QTableWidgetItem *item_2 =  new QTableWidgetItem(QString::number(quantity[i]*needed[i]));
        item_2->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget_4->setItem(i, 2, item_2);
        total_wit += quantity[i]*needed[i];
        // mora cost
        QTableWidgetItem *item_3 =  new QTableWidgetItem(QString::number(quantity[i]*needed[i]*4000));
        item_3->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget_4->setItem(i, 3, item_3);
        total_mora += quantity[i]*needed[i]*4000;
        // total mora cost
        QTableWidgetItem *item_4 =  new QTableWidgetItem(QString::number(total_mora));
        item_4->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget_4->setItem(i, 4, item_4);
    }

    QTableWidgetItem *item_5 =  new QTableWidgetItem(QString::number(total_wit));
    item_5->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_4->setItem(7, 2, item_5);

    QTableWidgetItem *item_6 =  new QTableWidgetItem(QString::number(total_mora));
    item_6->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_4->setItem(7, 3, item_6);

    QTableWidgetItem *item_7 =  new QTableWidgetItem(QString::number(total_mora));
    item_7->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_4->setItem(7, 4, item_7);

    QTableWidgetItem *item_8 =  new QTableWidgetItem(QString::number(ui->tableWidget_4->item(7, 4)->text().toInt() + ascen_mora));
    item_8->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_11->setItem(0, 0, item_8);
}

void genshin_calculator::talent(QString val){

    QJsonDocument jsonResponse = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject jsonObject = jsonResponse.object();
    QJsonArray jsonArray = jsonObject["training"].toArray();
    QJsonArray jsonArray_2 = jsonObject["characters"].toArray();

    QJsonObject tmp;
    int mora_1_6 = 0;
    int mora_7_8 = 0;
    int mora_9_10 = 0;
    for (int i=0; i<jsonArray.size(); i++) {
        tmp = jsonArray.at(i).toObject();
        int needed[] = {0,0,0};
        int common_needed[] = {0,0,0};
        int weekly = 0;
        if (tmp["Check"].toBool()){
            if ((tmp["Normal attack lvl"].toString().toInt() < 2) && (tmp["Normal attack target lvl"].toString().toInt() >= 2)){
                needed[2] += 3;
                common_needed[2] += 6;
                mora_1_6 += 12500;
            }
            if ((tmp["Normal attack lvl"].toString().toInt() < 3) && (tmp["Normal attack target lvl"].toString().toInt() >= 3)){
                needed[1] += 2;
                common_needed[1] += 3;
                mora_1_6 += 17500;
            }
            if ((tmp["Normal attack lvl"].toString().toInt() < 4) && (tmp["Normal attack target lvl"].toString().toInt() >= 4)){
                needed[1] += 4;
                common_needed[1] += 4;
                mora_1_6 += 25000;
            }
            if ((tmp["Normal attack lvl"].toString().toInt() < 5) && (tmp["Normal attack target lvl"].toString().toInt() >= 5)){
                needed[1] += 6;
                common_needed[1] += 6;
                mora_1_6 += 30000;
            }
            if ((tmp["Normal attack lvl"].toString().toInt() < 6) && (tmp["Normal attack target lvl"].toString().toInt() >= 6)){
                needed[1] += 9;
                common_needed[1] += 9;
                mora_1_6 += 37500;
            }
            if ((tmp["Normal attack lvl"].toString().toInt() < 7) && (tmp["Normal attack target lvl"].toString().toInt() >= 7)){
                needed[0] += 4;
                common_needed[0] += 4;
                mora_7_8 += 120000;
                weekly++;
            }
            if ((tmp["Normal attack lvl"].toString().toInt() < 8) && (tmp["Normal attack target lvl"].toString().toInt() >= 8)){
                needed[0] += 6;
                common_needed[0] += 6;
                mora_7_8 += 260000;
                weekly++;
            }
            if ((tmp["Normal attack lvl"].toString().toInt() < 9) && (tmp["Normal attack target lvl"].toString().toInt() >= 9)){
                needed[0] += 12;
                common_needed[0] += 9;
                mora_9_10 += 450000;
                weekly+=2;
            }
            if ((tmp["Normal attack lvl"].toString().toInt() < 10) && (tmp["Normal attack target lvl"].toString().toInt() >= 10)){
                needed[0] += 16;
                common_needed[0] += 12;
                mora_9_10 += 700000;
                weekly+=2;
            }


            if ((tmp["Elemental skill lvl"].toString().toInt() < 2) && (tmp["Elemental skill target lvl"].toString().toInt() >= 2)){
                needed[2] += 3;
                common_needed[2] += 6;
                mora_1_6 += 12500;
            }
            if ((tmp["Elemental skill lvl"].toString().toInt() < 3) && (tmp["Elemental skill target lvl"].toString().toInt() >= 3)){
                needed[1] += 2;
                common_needed[1] += 3;
                mora_1_6 += 17500;
            }
            if ((tmp["Elemental skill lvl"].toString().toInt() < 4) && (tmp["Elemental skill target lvl"].toString().toInt() >= 4)){
                needed[1] += 4;
                common_needed[1] += 4;
                mora_1_6 += 25000;
            }
            if ((tmp["Elemental skill lvl"].toString().toInt() < 5) && (tmp["Elemental skill target lvl"].toString().toInt() >= 5)){
                needed[1] += 6;
                common_needed[1] += 6;
                mora_1_6 += 30000;
            }
            if ((tmp["Elemental skill lvl"].toString().toInt() < 6) && (tmp["Elemental skill target lvl"].toString().toInt() >= 6)){
                needed[1] += 9;
                common_needed[1] += 9;
                mora_1_6 += 37500;
            }
            if ((tmp["Elemental skill lvl"].toString().toInt() < 7) && (tmp["Elemental skill target lvl"].toString().toInt() >= 7)){
                needed[0] += 4;
                common_needed[0] += 4;
                mora_7_8 += 120000;
                weekly++;
            }
            if ((tmp["Elemental skill lvl"].toString().toInt() < 8) && (tmp["Elemental skill target lvl"].toString().toInt() >= 8)){
                needed[0] += 6;
                common_needed[0] += 6;
                mora_7_8 += 260000;
                weekly++;
            }
            if ((tmp["Elemental skill lvl"].toString().toInt() < 9) && (tmp["Elemental skill target lvl"].toString().toInt() >= 9)){
                needed[0] += 12;
                common_needed[0] += 9;
                mora_9_10 += 450000;
                weekly+=2;
            }
            if ((tmp["Elemental skill lvl"].toString().toInt() < 10) && (tmp["Elemental skill target lvl"].toString().toInt() >= 10)){
                needed[0] += 16;
                common_needed[0] += 12;
                mora_9_10 += 700000;
                weekly+=2;
            }


            if ((tmp["Elemental burst lvl"].toString().toInt() < 2) && (tmp["Elemental burst target lvl"].toString().toInt() >= 2)){
                needed[2] += 3;
                common_needed[2] += 6;
                mora_1_6 += 12500;
            }
            if ((tmp["Elemental burst lvl"].toString().toInt() < 3) && (tmp["Elemental burst target lvl"].toString().toInt() >= 3)){
                needed[1] += 2;
                common_needed[1] += 3;
                mora_1_6 += 17500;
            }
            if ((tmp["Elemental burst lvl"].toString().toInt() < 4) && (tmp["Elemental burst target lvl"].toString().toInt() >= 4)){
                needed[1] += 4;
                common_needed[1] += 4;
                mora_1_6 += 25000;
            }
            if ((tmp["Elemental burst lvl"].toString().toInt() < 5) && (tmp["Elemental burst target lvl"].toString().toInt() >= 5)){
                needed[1] += 6;
                common_needed[1] += 6;
                mora_1_6 += 30000;
            }
            if ((tmp["Elemental burst lvl"].toString().toInt() < 6) && (tmp["Elemental burst target lvl"].toString().toInt() >= 6)){
                needed[1] += 9;
                common_needed[1] += 9;
                mora_1_6 += 37500;
            }
            if ((tmp["Elemental burst lvl"].toString().toInt() < 7) && (tmp["Elemental burst target lvl"].toString().toInt() >= 7)){
                needed[0] += 4;
                common_needed[0] += 4;
                mora_7_8 += 120000;
                weekly++;
            }
            if ((tmp["Elemental burst lvl"].toString().toInt() < 8) && (tmp["Elemental burst target lvl"].toString().toInt() >= 8)){
                needed[0] += 6;
                common_needed[0] += 6;
                mora_7_8 += 260000;
                weekly++;
            }
            if ((tmp["Elemental burst lvl"].toString().toInt() < 9) && (tmp["Elemental burst target lvl"].toString().toInt() >= 9)){
                needed[0] += 12;
                common_needed[0] += 9;
                mora_9_10 += 450000;
                weekly+=2;
            }
            if ((tmp["Elemental burst lvl"].toString().toInt() < 10) && (tmp["Elemental burst target lvl"].toString().toInt() >= 10)){
                needed[0] += 16;
                common_needed[0] += 12;
                mora_9_10 += 700000;
                weekly+=2;
            }

            if (weekly > 0){
                for (int i=0; i<jsonArray_2.size(); i++) {
                    QJsonObject tmp2 = jsonArray_2.at(i).toObject();
                    bool already_exist = false;
                    int row = 0;
                    if (tmp["Name"].toString() == tmp2["Name"].toString()){

                        for (int i=0; i<ui->tableWidget_14->rowCount(); i++)
                            if (ui->tableWidget_14->item(i, 0)->text() == tmp2["Weekly material"].toString()){
                                already_exist = true;
                                row = i;
                            }

                        if (already_exist){
                            weekly += ui->tableWidget_14->item(row, 1)->text().toInt();
                            QTableWidgetItem *item =  new QTableWidgetItem(QString::number(weekly));
                            item->setTextAlignment(Qt::AlignCenter);
                            ui->tableWidget_14->setItem(row, 1, item);
                        }
                        else{
                            ui->tableWidget_14->insertRow(ui->tableWidget_14->rowCount());
                            QTableWidgetItem *item =  new QTableWidgetItem(tmp2["Weekly material"].toString());
                            ui->tableWidget_14->setItem(ui->tableWidget_14->rowCount()-1, 0, item);
                            QTableWidgetItem *item_2 =  new QTableWidgetItem(QString::number(weekly));
                            item_2->setTextAlignment(Qt::AlignCenter);
                            ui->tableWidget_14->setItem(ui->tableWidget_14->rowCount()-1, 1, item_2);
                        }
                    }
                }
            }

            for (int i=0; i<jsonArray_2.size(); i++) {

                QJsonObject tmp2 = jsonArray_2.at(i).toObject();
                int row = 0;
                if (tmp["Name"].toString() == tmp2["Name"].toString()){
                    for (int i=0; i<ui->tableWidget_8->rowCount(); i++)
                        if (ui->tableWidget_8->item(i, 0)->text() == tmp2["Talent material"].toString())
                            row = i;

                    if (ui->tableWidget_8->item(row, 3) != nullptr)
                        needed[2] += ui->tableWidget_8->item(row, 3)->text().toInt();
                    if (ui->tableWidget_8->item(row, 2) != nullptr)
                        needed[1] += ui->tableWidget_8->item(row, 2)->text().toInt();
                    if (ui->tableWidget_8->item(row, 1) != nullptr)
                        needed[0] += ui->tableWidget_8->item(row, 1)->text().toInt();
                    QTableWidgetItem *item_2 =  new QTableWidgetItem(QString::number(needed[2]));
                    QTableWidgetItem *item_3 =  new QTableWidgetItem(QString::number(needed[1]));
                    QTableWidgetItem *item_4 =  new QTableWidgetItem(QString::number(needed[0]));
                    item_2->setTextAlignment(Qt::AlignCenter);
                    item_3->setTextAlignment(Qt::AlignCenter);
                    item_4->setTextAlignment(Qt::AlignCenter);
                    if (needed[2] > 0)
                        ui->tableWidget_8->setItem(row, 3, item_2);
                    if (needed[1] > 0)
                        ui->tableWidget_8->setItem(row, 2, item_3);
                    if (needed[0] > 0)
                        ui->tableWidget_8->setItem(row, 1, item_4);
                }
            }

            for (int i=0; i<jsonArray_2.size(); i++) {
                QJsonObject tmp2 = jsonArray_2.at(i).toObject();
                int row = 0;
                if (tmp["Name"].toString() == tmp2["Name"].toString()){
                    for (int i=0; i<ui->tableWidget_10->rowCount(); i++)
                        if (ui->tableWidget_10->item(i, 0)->text() == tmp2["Common material"].toString())
                            row = i;

                    if (ui->tableWidget_10->item(row, 3) != nullptr)
                        common_needed[2] += ui->tableWidget_10->item(row, 3)->text().toInt();
                    if (ui->tableWidget_10->item(row, 2) != nullptr)
                        common_needed[1] += ui->tableWidget_10->item(row, 2)->text().toInt();
                    if (ui->tableWidget_10->item(row, 1) != nullptr)
                        common_needed[0] += ui->tableWidget_10->item(row, 1)->text().toInt();
                    QTableWidgetItem *item_2 =  new QTableWidgetItem(QString::number(common_needed[2]));
                    QTableWidgetItem *item_3 =  new QTableWidgetItem(QString::number(common_needed[1]));
                    QTableWidgetItem *item_4 =  new QTableWidgetItem(QString::number(common_needed[0]));
                    item_2->setTextAlignment(Qt::AlignCenter);
                    item_3->setTextAlignment(Qt::AlignCenter);
                    item_4->setTextAlignment(Qt::AlignCenter);
                    if (common_needed[2] > 0)
                        ui->tableWidget_10->setItem(row, 3, item_2);
                    if (common_needed[1] > 0)
                        ui->tableWidget_10->setItem(row, 2, item_3);
                    if (common_needed[0] > 0)
                        ui->tableWidget_10->setItem(row, 1, item_4);
                }
            }
        }
    }

    QTableWidgetItem *item =  new QTableWidgetItem(QString::number(mora_1_6));
    QTableWidgetItem *item_2 =  new QTableWidgetItem(QString::number(mora_7_8));
    QTableWidgetItem *item_3 =  new QTableWidgetItem(QString::number(mora_9_10));
    QTableWidgetItem *item_4 =  new QTableWidgetItem(QString::number(mora_1_6 + mora_7_8 + mora_9_10 + ui->tableWidget_11->item(0, 0)->text().toInt()));
    item->setTextAlignment(Qt::AlignCenter);
    item_2->setTextAlignment(Qt::AlignCenter);
    item_3->setTextAlignment(Qt::AlignCenter);
    item_4->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_11->setItem(1, 0, item);
    ui->tableWidget_11->setItem(2, 0, item_2);
    ui->tableWidget_11->setItem(3, 0, item_3);
    ui->tableWidget_11->setItem(4, 0, item_4);
}

void genshin_calculator::calculate_weapons(QString val){

    QJsonDocument jsonResponse = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject jsonObject = jsonResponse.object();
    QJsonArray jsonArray = jsonObject["weapon_training"].toArray();
    //QJsonArray jsonArray_2 = jsonObject["weapons"].toArray();

    QJsonObject tmp;
    int quantity[] = {0,0,0,0,0,0,0};
    int quantity2[] = {0,0,0,0,0,0,0};
    int quantity3[] = {0,0,0,0,0,0,0};
    int needed_5[] = {12,63,63,93,130,175,372};
    int needed_4[] = {8,41,42,62,87,117,248};
    int needed_3[] = {6,28,28,41,58,77,164};

    //int ascen_mora = 0;
    for (int i=0; i<jsonArray.size(); i++) {
        tmp = jsonArray.at(i).toObject();
        if (tmp["Check"].toBool()){
            //int phase = tmp["Phase"].toString().toInt();
            int curr = tmp["Current level"].toString().toInt();
            int targ = tmp["Target level"].toString().toInt();
            if (curr < 20 && curr < targ){
                if (tmp["Rarity"] == "*****")
                    quantity[0]++;
                if (tmp["Rarity"] == "****")
                    quantity2[0]++;
                if (tmp["Rarity"] == "***")
                    quantity3[0]++;
            }
            if (curr < 40 && curr < targ){
                if (tmp["Rarity"] == "*****")
                    quantity[1]++;
                if (tmp["Rarity"] == "****")
                    quantity2[1]++;
                if (tmp["Rarity"] == "***")
                    quantity3[1]++;
            }
            if (curr < 50 && curr < targ){
                if (tmp["Rarity"] == "*****")
                    quantity[2]++;
                if (tmp["Rarity"] == "****")
                    quantity2[2]++;
                if (tmp["Rarity"] == "***")
                    quantity3[2]++;
            }
            if (curr < 60 && curr < targ){
                if (tmp["Rarity"] == "*****")
                    quantity[3]++;
                if (tmp["Rarity"] == "****")
                    quantity2[3]++;
                if (tmp["Rarity"] == "***")
                    quantity3[3]++;
            }
            if (curr < 70 && curr < targ){
                if (tmp["Rarity"] == "*****")
                    quantity[4]++;
                if (tmp["Rarity"] == "****")
                    quantity2[4]++;
                if (tmp["Rarity"] == "***")
                    quantity3[4]++;
            }
            if (curr < 80 && curr < targ){
                if (tmp["Rarity"] == "*****")
                    quantity[5]++;
                if (tmp["Rarity"] == "****")
                    quantity2[5]++;
                if (tmp["Rarity"] == "***")
                    quantity3[5]++;
            }
            if (curr < 90 && curr < targ){
                if (tmp["Rarity"] == "*****")
                    quantity[6]++;
                if (tmp["Rarity"] == "****")
                    quantity2[6]++;
                if (tmp["Rarity"] == "***")
                    quantity3[6]++;
            }
        }
    }

    int total_mora = 0;
    int total_ore = 0;
    int total_ore2 = 0;
    int total_ore3 = 0;
    for (int i=0; i < 7; i++ ) {
        QTableWidgetItem *item_2 =  new QTableWidgetItem(QString::number(quantity[i]) + " x " + QString::number(needed_5[i]) + " = " + QString::number(quantity[i]*needed_5[i]));
        item_2->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget_15->setItem(i, 1, item_2);
        QTableWidgetItem *item_3 =  new QTableWidgetItem(QString::number(quantity2[i]) + " x " + QString::number(needed_4[i]) + " = " + QString::number(quantity2[i]*needed_4[i]));
        item_3->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget_15->setItem(i, 2, item_3);
        QTableWidgetItem *item_4 =  new QTableWidgetItem(QString::number(quantity3[i]) + " x " + QString::number(needed_3[i]) + " = " + QString::number(quantity3[i]*needed_3[i]));
        item_4->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget_15->setItem(i, 3, item_4);

        total_mora += quantity[i]*needed_5[i]*1000;
        total_mora += quantity2[i]*needed_4[i]*1000;
        total_mora += quantity3[i]*needed_3[i]*1000;

        total_ore += quantity[i]*needed_5[i];
        total_ore2 += quantity2[i]*needed_4[i];
        total_ore3 += quantity3[i]*needed_3[i];

        QTableWidgetItem *item_5 =  new QTableWidgetItem(QString::number(quantity[i]*needed_5[i]*1000 + quantity2[i]*needed_4[i]*1000 + quantity3[i]*needed_3[i]*1000));
        item_5->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget_15->setItem(i, 4, item_5);
        QTableWidgetItem *item_6 =  new QTableWidgetItem(QString::number(total_mora));
        item_6->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget_15->setItem(i, 5, item_6);
    }

    QTableWidgetItem *item_6 =  new QTableWidgetItem(QString::number(total_ore));
    item_6->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_15->setItem(7, 1, item_6);
    QTableWidgetItem *item_7 =  new QTableWidgetItem(QString::number(total_ore2));
    item_7->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_15->setItem(7, 2, item_7);
    QTableWidgetItem *item_8 =  new QTableWidgetItem(QString::number(total_ore3));
    item_8->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_15->setItem(7, 3, item_8);
    QTableWidgetItem *item_9 =  new QTableWidgetItem(QString::number(total_mora));
    item_9->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_15->setItem(7, 4, item_9);
    QTableWidgetItem *item_10 =  new QTableWidgetItem(QString::number(total_mora));
    item_10->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_15->setItem(7, 5, item_10);
/*
    QTableWidgetItem *item_5 =  new QTableWidgetItem(QString::number(total_wit));
    item_5->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_4->setItem(7, 2, item_5);

    QTableWidgetItem *item_6 =  new QTableWidgetItem(QString::number(total_mora));
    item_6->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_4->setItem(7, 3, item_6);

    QTableWidgetItem *item_7 =  new QTableWidgetItem(QString::number(total_mora));
    item_7->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_4->setItem(7, 4, item_7);

    QTableWidgetItem *item_8 =  new QTableWidgetItem(QString::number(ui->tableWidget_4->item(7, 4)->text().toInt() + ascen_mora));
    item_8->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_11->setItem(0, 0, item_8);*/

    resize_layouts();
}

void genshin_calculator::update_char_list(){

    QString val;
    QFile file;
    file.setFileName(filepath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject obj = jsonResponse.object();

    ui->listWidget_7->clear();
    ui->tableWidget_2->setRowCount(0);
    QJsonObject tmp;
    QJsonArray array = obj["characters"].toArray();
    for (int i = 0; i<array.size(); i++){
        tmp = array.at(i).toObject();
        ui->listWidget_7->addItem(tmp["Name"].toString());
        ui->tableWidget_2->insertRow(ui->tableWidget_2->rowCount());

        QTableWidgetItem *item = new QTableWidgetItem(tmp["Name"].toString());
        QTableWidgetItem *item_2 = new QTableWidgetItem(tmp["Vision"].toString());
        QTableWidgetItem *item_3 = new QTableWidgetItem(tmp["Region"].toString());
        QTableWidgetItem *item_4 = new QTableWidgetItem(tmp["Common material"].toString());
        QTableWidgetItem *item_5 = new QTableWidgetItem(tmp["Ascension material"].toString());
        QTableWidgetItem *item_6 = new QTableWidgetItem(tmp["Local speciality"].toString());
        QTableWidgetItem *item_7 = new QTableWidgetItem(tmp["Talent material"].toString());
        QTableWidgetItem *item_8 = new QTableWidgetItem(tmp["Weekly material"].toString());

        item->setTextAlignment(Qt::AlignVCenter);
        item_2->setTextAlignment(Qt::AlignVCenter);
        item_3->setTextAlignment(Qt::AlignVCenter);
        item_4->setTextAlignment(Qt::AlignVCenter);
        item_5->setTextAlignment(Qt::AlignVCenter);
        item_6->setTextAlignment(Qt::AlignVCenter);
        item_7->setTextAlignment(Qt::AlignVCenter);

        ui->tableWidget_2->setItem(i, 0, item);
        ui->tableWidget_2->setItem(i, 1, item_2);
        ui->tableWidget_2->setItem(i, 2, item_3);
        ui->tableWidget_2->setItem(i, 3, item_4);
        ui->tableWidget_2->setItem(i, 4, item_5);
        ui->tableWidget_2->setItem(i, 5, item_6);
        ui->tableWidget_2->setItem(i, 6, item_7);
        ui->tableWidget_2->setItem(i, 7, item_8);
    }

    resize_layouts();
}

void genshin_calculator::update_training_list(){

    QString val;
    QFile file;
    file.setFileName(filepath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject obj = jsonResponse.object();

    ui->tableWidget->setRowCount(0);
    QJsonObject tmp;
    QJsonArray jsonArray = obj["training"].toArray();
    for (int i = 0; i<jsonArray.size(); i++){
        tmp = jsonArray.at(i).toObject();
        ui->tableWidget->insertRow(i);
        QTableWidgetItem *item = new QTableWidgetItem(tmp["Name"].toString());
        if (tmp["Check"].toBool())
            item->setCheckState(Qt::Checked);
        else
            item->setCheckState(Qt::Unchecked);
        ui->tableWidget->setItem(i, 0, item);
        QTableWidgetItem *item_2 =  new QTableWidgetItem(tmp["Current lvl"].toString());
        QTableWidgetItem *item_3 =  new QTableWidgetItem(tmp["Target lvl"].toString());
        QTableWidgetItem *item_4 =  new QTableWidgetItem(tmp["Phase"].toString());
        QTableWidgetItem *item_5 =  new QTableWidgetItem(tmp["Normal attack lvl"].toString());
        QTableWidgetItem *item_6 =  new QTableWidgetItem(tmp["Normal attack target lvl"].toString());
        QTableWidgetItem *item_7 =  new QTableWidgetItem(tmp["Elemental skill lvl"].toString());
        QTableWidgetItem *item_8 =  new QTableWidgetItem(tmp["Elemental skill target lvl"].toString());
        QTableWidgetItem *item_9 =  new QTableWidgetItem(tmp["Elemental burst lvl"].toString());
        QTableWidgetItem *item_10 =  new QTableWidgetItem(tmp["Elemental burst target lvl"].toString());

        item_2->setTextAlignment(Qt::AlignCenter);
        item_3->setTextAlignment(Qt::AlignCenter);
        item_4->setTextAlignment(Qt::AlignCenter);
        item_5->setTextAlignment(Qt::AlignCenter);
        item_5->setBackground(QColor(210,255,255));
        item_6->setTextAlignment(Qt::AlignCenter);
        item_6->setBackground(QColor(166,198,199));
        item_7->setTextAlignment(Qt::AlignCenter);
        item_7->setBackground(QColor(210,255,255));
        item_8->setTextAlignment(Qt::AlignCenter);
        item_8->setBackground(QColor(166,198,199));
        item_9->setTextAlignment(Qt::AlignCenter);
        item_9->setBackground(QColor(210,255,255));
        item_10->setTextAlignment(Qt::AlignCenter);
        item_10->setBackground(QColor(166,198,199));

        ui->tableWidget->setItem(i, 1, item_2);
        ui->tableWidget->setItem(i, 2, item_3);
        ui->tableWidget->setItem(i, 3, item_4);
        ui->tableWidget->setItem(i, 4, item_5);
        ui->tableWidget->setItem(i, 5, item_6);
        ui->tableWidget->setItem(i, 6, item_7);
        ui->tableWidget->setItem(i, 7, item_8);
        ui->tableWidget->setItem(i, 8, item_9);
        ui->tableWidget->setItem(i, 9, item_10);

    }

    resize_layouts();
}

void genshin_calculator::update_weapon_list(){

    QString val;
    QFile file;
    file.setFileName(filepath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject obj = jsonResponse.object();

    ui->listWidget_8->clear();
    ui->tableWidget_13->setRowCount(0);
    QJsonObject tmp;
    QJsonArray array = obj["weapons"].toArray();
    for (int i = 0; i<array.size(); i++){
        tmp = array.at(i).toObject();
        ui->listWidget_8->addItem(tmp["Name"].toString());
        ui->tableWidget_13->insertRow(ui->tableWidget_13->rowCount());

        QTableWidgetItem *item = new QTableWidgetItem(tmp["Name"].toString());
        QTableWidgetItem *item_2 = new QTableWidgetItem(tmp["Type"].toString());
        if (tmp["Rarity"].toString() == "*****"){
            QTableWidgetItem *item_3 = new QTableWidgetItem("★★★★★");
            item_3->setTextAlignment(Qt::AlignVCenter);
            ui->tableWidget_13->setItem(i, 2, item_3);
        }
        if (tmp["Rarity"].toString() == "****"){
            QTableWidgetItem *item_3 = new QTableWidgetItem("★★★★");
            item_3->setTextAlignment(Qt::AlignVCenter);
            ui->tableWidget_13->setItem(i, 2, item_3);
        }
        if (tmp["Rarity"].toString() == "***"){
            QTableWidgetItem *item_3 = new QTableWidgetItem("★★★");
            item_3->setTextAlignment(Qt::AlignVCenter);
            ui->tableWidget_13->setItem(i, 2, item_3);
        }
        QTableWidgetItem *item_4 = new QTableWidgetItem(tmp["Common material"].toString());
        QTableWidgetItem *item_5 = new QTableWidgetItem(tmp["Elite material"].toString());
        QTableWidgetItem *item_6 = new QTableWidgetItem(tmp["Weapon material"].toString());

        item->setTextAlignment(Qt::AlignVCenter);
        item_2->setTextAlignment(Qt::AlignVCenter);
        item_4->setTextAlignment(Qt::AlignVCenter);
        item_5->setTextAlignment(Qt::AlignVCenter);
        item_6->setTextAlignment(Qt::AlignVCenter);

        ui->tableWidget_13->setItem(i, 0, item);
        ui->tableWidget_13->setItem(i, 1, item_2);
        ui->tableWidget_13->setItem(i, 3, item_4);
        ui->tableWidget_13->setItem(i, 4, item_5);
        ui->tableWidget_13->setItem(i, 5, item_6);
    }

    resize_layouts();
}

void genshin_calculator::update_weapon_training_list(){

    QString val;
    QFile file;
    file.setFileName(filepath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject obj = jsonResponse.object();

    ui->tableWidget_3->setRowCount(0);
    QJsonObject tmp;
    QJsonArray jsonArray = obj["weapon_training"].toArray();
    for (int i = 0; i<jsonArray.size(); i++){
        tmp = jsonArray.at(i).toObject();
        ui->tableWidget_3->insertRow(i);
        QTableWidgetItem *item = new QTableWidgetItem(tmp["Name"].toString());
        if (tmp["Check"].toBool())
            item->setCheckState(Qt::Checked);
        else
            item->setCheckState(Qt::Unchecked);
        ui->tableWidget_3->setItem(i, 0, item);
        QTableWidgetItem *item_2 =  new QTableWidgetItem(tmp["Type"].toString());
        item_2->setTextAlignment(Qt::AlignVCenter);
        ui->tableWidget_3->setItem(i, 1, item_2);

        if (tmp["Rarity"].toString() == "*****"){
            QTableWidgetItem *item_3 = new QTableWidgetItem("★★★★★");
            item_3->setTextAlignment(Qt::AlignVCenter);
            ui->tableWidget_3->setItem(i, 2, item_3);
        }
        if (tmp["Rarity"].toString() == "****"){
            QTableWidgetItem *item_3 = new QTableWidgetItem("★★★★");
            item_3->setTextAlignment(Qt::AlignVCenter);
            ui->tableWidget_3->setItem(i, 2, item_3);
        }
        if (tmp["Rarity"].toString() == "***"){
            QTableWidgetItem *item_3 = new QTableWidgetItem("★★★");
            item_3->setTextAlignment(Qt::AlignVCenter);
            ui->tableWidget_3->setItem(i, 2, item_3);
        }
        QTableWidgetItem *item_4 = new QTableWidgetItem(tmp["Phase"].toString());
        QTableWidgetItem *item_5 = new QTableWidgetItem(tmp["Current level"].toString());
        QTableWidgetItem *item_6 = new QTableWidgetItem(tmp["Target level"].toString());

        item_4->setTextAlignment(Qt::AlignCenter);
        item_5->setTextAlignment(Qt::AlignCenter);
        item_6->setTextAlignment(Qt::AlignCenter);

        ui->tableWidget_3->setItem(i, 3, item_4);
        ui->tableWidget_3->setItem(i, 4, item_5);
        ui->tableWidget_3->setItem(i, 5, item_6);
    }

    resize_layouts();
}

void genshin_calculator::resize_layouts(){

    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->resizeRowsToContents();
    ui->tableWidget_2->resizeColumnsToContents();
    ui->tableWidget_2->resizeRowsToContents();
    ui->tableWidget_3->resizeColumnsToContents();
    ui->tableWidget_3->resizeRowsToContents();
    ui->tableWidget_4->resizeColumnsToContents();
    ui->tableWidget_4->resizeRowsToContents();
    ui->tableWidget_5->resizeColumnsToContents();
    ui->tableWidget_5->resizeRowsToContents();
    ui->tableWidget_6->resizeColumnsToContents();
    ui->tableWidget_6->resizeRowsToContents();
    ui->tableWidget_7->resizeColumnsToContents();
    ui->tableWidget_7->resizeRowsToContents();
    ui->tableWidget_8->resizeColumnsToContents();
    ui->tableWidget_8->resizeRowsToContents();
    ui->tableWidget_9->resizeColumnsToContents();
    ui->tableWidget_9->resizeRowsToContents();
    ui->tableWidget_10->resizeColumnsToContents();
    ui->tableWidget_10->resizeRowsToContents();
    ui->tableWidget_11->resizeColumnsToContents();
    ui->tableWidget_11->resizeRowsToContents();
    ui->tableWidget_12->resizeColumnsToContents();
    ui->tableWidget_12->resizeRowsToContents();
    ui->tableWidget_13->resizeColumnsToContents();
    ui->tableWidget_13->resizeRowsToContents();
    ui->tableWidget_14->resizeColumnsToContents();
    ui->tableWidget_14->resizeRowsToContents();
    ui->tableWidget_15->resizeColumnsToContents();
    ui->tableWidget_15->resizeRowsToContents();


}

void genshin_calculator::add_new_material(int n){

    QString val;
    QFile file;
    file.setFileName(filepath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject jsonObject = jsonResponse.object();

    switch(n) {
    case 1:{
        QJsonArray jsonArray = jsonObject["common_materials"].toArray();
        jsonArray.append(ui->lineEdit_8->text());
        jsonObject.insert("common_materials", jsonArray);
        ui->lineEdit_8->clear();
        break;
        }
    case 2:{
        QJsonArray jsonArray = jsonObject["ascension_materials"].toArray();
        jsonArray.append(ui->lineEdit_10->text());
        jsonObject.insert("ascension_materials", jsonArray);
        ui->lineEdit_10->clear();
        break;
        }
    case 3:{
        QJsonArray jsonArray = jsonObject["elite_materials"].toArray();
        jsonArray.append(ui->lineEdit_11->text());
        jsonObject.insert("elite_materials", jsonArray);
        ui->lineEdit_11->clear();
        break;
    }
    case 4:{
        QJsonArray jsonArray = jsonObject["weapon_materials"].toArray();
        jsonArray.append(ui->lineEdit_14->text());
        jsonObject.insert("weapon_materials", jsonArray);
        ui->lineEdit_14->clear();
        break;
    }
    case 5:{
        QJsonArray jsonArray = jsonObject["local_materials"].toArray();
        jsonArray.append(ui->lineEdit_9->text());
        jsonObject.insert("local_materials", jsonArray);
        ui->lineEdit_9->clear();
        break;
    }
    case 6:{
        QJsonArray jsonArray = jsonObject["talent_materials"].toArray();
        jsonArray.append(ui->lineEdit_12->text());
        jsonObject.insert("talent_materials", jsonArray);
        ui->lineEdit_12->clear();
        break;
    }
    case 7:{
        QJsonArray jsonArray = jsonObject["weekly_materials"].toArray();
        jsonArray.append(ui->lineEdit_13->text());
        jsonObject.insert("weekly_materials", jsonArray);
        ui->lineEdit_13->clear();
        break;
    }}

    jsonResponse.setObject(jsonObject);
    file.open(QIODevice::ReadWrite | QIODevice::Text| QFile::Truncate);
    file.write(jsonResponse.toJson());
    file.close();

    refresh_items();
}

void genshin_calculator::remove_material(int n){

    QString val;
    QFile file;
    file.setFileName(filepath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject jsonObject = jsonResponse.object();

    switch(n) {
    case 1:{
        QJsonArray jsonArray = jsonObject["common_materials"].toArray();
        jsonArray.removeAt(ui->listWidget->currentRow());
        jsonObject.insert("common_materials", jsonArray);
        ui->lineEdit_8->clear();
        break;
        }
    case 2:{
        QJsonArray jsonArray = jsonObject["ascension_materials"].toArray();
        jsonArray.removeAt(ui->listWidget_2->currentRow());
        jsonObject.insert("ascension_materials", jsonArray);
        ui->lineEdit_10->clear();
        break;
        }
    case 3:{
        QJsonArray jsonArray = jsonObject["elite_materials"].toArray();
        jsonArray.removeAt(ui->listWidget_3->currentRow());
        jsonObject.insert("elite_materials", jsonArray);
        ui->lineEdit_11->clear();
        break;
    }
    case 4:{
        QJsonArray jsonArray = jsonObject["weapon_materials"].toArray();
        jsonArray.removeAt(ui->listWidget_9->currentRow());
        jsonObject.insert("weapon_materials", jsonArray);
        ui->lineEdit_14->clear();
        break;
    }
    case 5:{
        QJsonArray jsonArray = jsonObject["local_materials"].toArray();
        jsonArray.removeAt(ui->listWidget_4->currentRow());
        jsonObject.insert("local_materials", jsonArray);
        ui->lineEdit_9->clear();
        break;
    }
    case 6:{
        QJsonArray jsonArray = jsonObject["talent_materials"].toArray();
        jsonArray.removeAt(ui->listWidget_5->currentRow());
        jsonObject.insert("talent_materials", jsonArray);
        ui->lineEdit_12->clear();
        break;
    }
    case 7:{
        QJsonArray jsonArray = jsonObject["weekly_materials"].toArray();
        jsonArray.removeAt(ui->listWidget_6->currentRow());
        jsonObject.insert("weekly_materials", jsonArray);
        ui->lineEdit_13->clear();
        break;
    }}

    jsonResponse.setObject(jsonObject);
    file.open(QIODevice::ReadWrite | QIODevice::Text | QFile::Truncate);
    file.write(jsonResponse.toJson());
    file.close();

    refresh_items();
}

// add common material
void genshin_calculator::on_pushButton_7_clicked()
{
    if (!ui->lineEdit_8->text().isEmpty())
        add_new_material(1);
}

// remove common material
void genshin_calculator::on_pushButton_8_clicked()
{
    remove_material(1);
}

// add ascension material
void genshin_calculator::on_pushButton_9_clicked()
{
    if (!ui->lineEdit_10->text().isEmpty())
        add_new_material(2);
}

// remove ascension material
void genshin_calculator::on_pushButton_10_clicked()
{
    remove_material(2);
}

// add elite material
void genshin_calculator::on_pushButton_11_clicked()
{
    if (!ui->lineEdit_11->text().isEmpty())
        add_new_material(3);
}

// remove elite material
void genshin_calculator::on_pushButton_12_clicked()
{
    remove_material(3);
}

// add weapon ascension material
void genshin_calculator::on_pushButton_24_clicked()
{
    if (!ui->lineEdit_14->text().isEmpty())
        add_new_material(4);
}

// remove weapon ascension material
void genshin_calculator::on_pushButton_23_clicked()
{
    remove_material(4);
}

// add local speciality
void genshin_calculator::on_pushButton_13_clicked()
{
    if (!ui->lineEdit_9->text().isEmpty())
        add_new_material(5);
}

// remove local speciality
void genshin_calculator::on_pushButton_14_clicked()
{
    remove_material(5);
}

// add talent material
void genshin_calculator::on_pushButton_15_clicked()
{
    if (!ui->lineEdit_12->text().isEmpty())
        add_new_material(6);
}

// remove talent materia
void genshin_calculator::on_pushButton_16_clicked()
{
    remove_material(6);
}

// add weekly material
void genshin_calculator::on_pushButton_17_clicked()
{
    if (!ui->lineEdit_13->text().isEmpty())
        add_new_material(7);
}

// remove weekly material
void genshin_calculator::on_pushButton_18_clicked()
{
    remove_material(7);
}

// add new character data
void genshin_calculator::on_pushButton_19_clicked()
{
    if (!ui->lineEdit->text().isEmpty()){

        QString val;
        QFile file;
        file.setFileName(filepath);
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        val = file.readAll();
        file.close();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(val.toUtf8());
        QJsonObject jsonObject = jsonResponse.object();
        QJsonArray jsonArray = jsonObject["characters"].toArray();
        QJsonArray jsonArray_2 = jsonObject["training"].toArray();

        // add new database entry
        QJsonObject new_char;
        new_char.insert("Name", ui->lineEdit->text());
        new_char.insert("Vision", ui->comboBox->currentText());
        new_char.insert("Region", ui->comboBox_2->currentText());
        new_char.insert("Common material", ui->comboBox_3->currentText());
        new_char.insert("Ascension material", ui->comboBox_4->currentText());
        new_char.insert("Local speciality", ui->comboBox_5->currentText());
        new_char.insert("Talent material", ui->comboBox_6->currentText());
        new_char.insert("Weekly material", ui->comboBox_7->currentText());
        jsonArray.append(new_char);
        jsonObject.insert("characters", jsonArray);

        // add new training entry
        QJsonObject new_training;
        new_training.insert("Name", ui->lineEdit->text());
        new_training.insert("Check", false);
        new_training.insert("Phase", QString::number(1));
        new_training.insert("Current lvl", QString::number(1));
        new_training.insert("Target lvl", QString::number(90));
        new_training.insert("Normal attack lvl", QString::number(1));
        new_training.insert("Normal attack target lvl", QString::number(8));
        new_training.insert("Elemental skill lvl", QString::number(1));
        new_training.insert("Elemental skill target lvl", QString::number(8));
        new_training.insert("Elemental burst lvl", QString::number(1));
        new_training.insert("Elemental burst target lvl", QString::number(8));
        jsonArray_2.append(new_training);
        jsonObject.insert("training", jsonArray_2);

        jsonResponse.setObject(jsonObject);
        file.open(QIODevice::ReadWrite | QIODevice::Text| QFile::Truncate);
        file.write(jsonResponse.toJson());
        file.close();

        ui->lineEdit->clear();
        update_char_list();
        update_training_list();
        calculate();
    }
}

// remove character data
void genshin_calculator::on_pushButton_4_clicked()
{
    QString val;
    QFile file;
    file.setFileName(filepath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject jsonObject = jsonResponse.object();
    QJsonArray jsonArray = jsonObject["characters"].toArray();
    QJsonArray jsonArray_2 = jsonObject["training"].toArray();
    jsonArray.removeAt(ui->listWidget_7->currentRow());
    jsonArray_2.removeAt(ui->listWidget_7->currentRow());
    jsonObject.insert("characters", jsonArray);
    jsonObject.insert("training", jsonArray_2);
    jsonResponse.setObject(jsonObject);
    file.open(QIODevice::ReadWrite | QIODevice::Text | QFile::Truncate);
    file.write(jsonResponse.toJson());
    file.close();

    ui->lineEdit->clear();
    update_char_list();
    update_training_list();
}

// edit character data
void genshin_calculator::on_pushButton_3_clicked()
{
    if(ui->listWidget_7->count() > 0){
        QString val;
        QFile file;
        file.setFileName(filepath);
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        val = file.readAll();
        file.close();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(val.toUtf8());
        QJsonObject jsonObject = jsonResponse.object();
        QJsonArray jsonArray = jsonObject["characters"].toArray();
        QJsonArray jsonArray_2 = jsonObject["training"].toArray();

        QJsonObject new_char;
        new_char.insert("Name", ui->lineEdit->text());
        new_char.insert("Vision", ui->comboBox->currentText());
        new_char.insert("Region", ui->comboBox_2->currentText());
        new_char.insert("Common material", ui->comboBox_3->currentText());
        new_char.insert("Ascension material", ui->comboBox_4->currentText());
        new_char.insert("Local speciality", ui->comboBox_5->currentText());
        new_char.insert("Talent material", ui->comboBox_6->currentText());
        new_char.insert("Weekly material", ui->comboBox_7->currentText());
        jsonArray.replace(ui->listWidget_7->currentRow(), new_char);
        jsonObject.insert("characters", jsonArray);


        QJsonObject tmp = jsonArray_2.at(ui->listWidget_7->currentRow()).toObject();
        tmp.insert("Name", ui->lineEdit->text());
        jsonArray_2.replace(ui->listWidget_7->currentRow(), tmp);
        jsonObject.insert("training", jsonArray_2);

        jsonResponse.setObject(jsonObject);
        file.open(QIODevice::ReadWrite | QIODevice::Text| QFile::Truncate);
        file.write(jsonResponse.toJson());
        file.close();

        ui->lineEdit->clear();
        update_char_list();
    }
}

// select character
void genshin_calculator::on_listWidget_7_itemSelectionChanged()
{
    QString val;
    QFile file;
    file.setFileName(filepath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject jsonObject = jsonResponse.object();
    QJsonArray jsonArray = jsonObject["characters"].toArray();
    QJsonObject tmp;
    tmp = jsonArray.at(ui->listWidget_7->currentRow()).toObject();
    ui->lineEdit->setText(tmp["Name"].toString());
    ui->comboBox->setCurrentIndex(ui->comboBox->findText(tmp["Vision"].toString()));
    ui->comboBox_2->setCurrentIndex(ui->comboBox_2->findText(tmp["Region"].toString()));
    ui->comboBox_3->setCurrentIndex(ui->comboBox_3->findText(tmp["Common material"].toString()));
    ui->comboBox_4->setCurrentIndex(ui->comboBox_4->findText(tmp["Ascension material"].toString()));
    ui->comboBox_5->setCurrentIndex(ui->comboBox_5->findText(tmp["Local speciality"].toString()));
    ui->comboBox_6->setCurrentIndex(ui->comboBox_6->findText(tmp["Talent material"].toString()));
    ui->comboBox_7->setCurrentIndex(ui->comboBox_7->findText(tmp["Weekly material"].toString()));
}

// save training list
void genshin_calculator::on_pushButton_clicked()
{
    QString val;
    QFile file;
    file.setFileName(filepath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject jsonObject = jsonResponse.object();
    QJsonArray jsonArray;

    for (int i = 0; i < ui->tableWidget->rowCount(); i++){
        QJsonObject new_char;
        new_char.insert("Name", ui->tableWidget->item(i, 0)->text());
        if (ui->tableWidget->item(i, 0)->checkState() == 2)
            new_char.insert("Check", true);
        if (ui->tableWidget->item(i, 0)->checkState() == 0)
            new_char.insert("Check", false);
        new_char.insert("Current lvl", ui->tableWidget->item(i, 1)->text());
        new_char.insert("Target lvl", ui->tableWidget->item(i, 2)->text());
        new_char.insert("Phase", ui->tableWidget->item(i, 3)->text());
        new_char.insert("Normal attack lvl", ui->tableWidget->item(i, 4)->text());
        new_char.insert("Normal attack target lvl", ui->tableWidget->item(i, 5)->text());
        new_char.insert("Elemental skill lvl", ui->tableWidget->item(i, 6)->text());
        new_char.insert("Elemental skill target lvl", ui->tableWidget->item(i, 7)->text());
        new_char.insert("Elemental burst lvl", ui->tableWidget->item(i, 8)->text());
        new_char.insert("Elemental burst target lvl", ui->tableWidget->item(i, 9)->text());
        jsonArray.append(new_char);
    }

    jsonObject.insert("training", jsonArray);
    jsonResponse.setObject(jsonObject);
    file.open(QIODevice::ReadWrite | QIODevice::Text| QFile::Truncate);
    file.write(jsonResponse.toJson());
    file.close();

    update_training_list();
    calculate();

}

// add new weapon data
void genshin_calculator::on_pushButton_20_clicked()
{
    if (!ui->lineEdit_2->text().isEmpty()){

        QString val;
        QFile file;
        file.setFileName(filepath);
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        val = file.readAll();
        file.close();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(val.toUtf8());
        QJsonObject jsonObject = jsonResponse.object();
        QJsonArray jsonArray = jsonObject["weapons"].toArray();
        QJsonArray jsonArray_2 = jsonObject["weapon_training"].toArray();

        // add new database entry
        QJsonObject new_char;
        new_char.insert("Name", ui->lineEdit_2->text());
        new_char.insert("Type", ui->comboBox_11->currentText());
        if (ui->comboBox_8->currentText() == "★★★★★")
            new_char.insert("Rarity", "*****");
        if (ui->comboBox_8->currentText() == "★★★★")
            new_char.insert("Rarity", "****");
        if (ui->comboBox_8->currentText() == "★★★")
            new_char.insert("Rarity", "***");
        new_char.insert("Common material", ui->comboBox_9->currentText());
        new_char.insert("Elite material", ui->comboBox_10->currentText());
        new_char.insert("Weapon material", ui->comboBox_12->currentText());
        jsonArray.append(new_char);
        jsonObject.insert("weapons", jsonArray);

        // add new training entry
        QJsonObject new_training;
        new_training.insert("Check", false);
        new_training.insert("Name", ui->lineEdit_2->text());
        new_training.insert("Type", ui->comboBox_11->currentText());
        if (ui->comboBox_8->currentText() == "★★★★★")
            new_training.insert("Rarity", "*****");
        if (ui->comboBox_8->currentText() == "★★★★")
            new_training.insert("Rarity", "****");
        if (ui->comboBox_8->currentText() == "★★★")
            new_training.insert("Rarity", "***");
        new_training.insert("Phase", QString::number(1));
        new_training.insert("Current level", QString::number(80));
        new_training.insert("Target level", QString::number(90));
        jsonArray_2.append(new_training);
        jsonObject.insert("weapon_training", jsonArray_2);

        jsonResponse.setObject(jsonObject);
        file.open(QIODevice::ReadWrite | QIODevice::Text| QFile::Truncate);
        file.write(jsonResponse.toJson());
        file.close();

        ui->lineEdit_2->clear();
        update_weapon_list();
        update_weapon_training_list();
        calculate();
    }
}

// remove weapon data
void genshin_calculator::on_pushButton_6_clicked()
{
    QString val;
    QFile file;
    file.setFileName(filepath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject jsonObject = jsonResponse.object();
    QJsonArray jsonArray = jsonObject["weapons"].toArray();
    QJsonArray jsonArray_2 = jsonObject["weapon_training"].toArray();
    jsonArray.removeAt(ui->listWidget_8->currentRow());
    jsonArray_2.removeAt(ui->listWidget_8->currentRow());
    jsonObject.insert("weapons", jsonArray);
    jsonObject.insert("weapon_training", jsonArray_2);
    jsonResponse.setObject(jsonObject);
    file.open(QIODevice::ReadWrite | QIODevice::Text | QFile::Truncate);
    file.write(jsonResponse.toJson());
    file.close();

    ui->lineEdit_2->clear();
    update_weapon_list();
    update_weapon_training_list();
}


void genshin_calculator::on_pushButton_22_clicked()
{
    QString val;
    QFile file;
    file.setFileName(filepath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject jsonObject = jsonResponse.object();
    QJsonArray jsonArray;

    for (int i = 0; i < ui->tableWidget_3->rowCount(); i++){
        QJsonObject new_char;
        new_char.insert("Name", ui->tableWidget_3->item(i, 0)->text());
        if (ui->tableWidget_3->item(i, 0)->checkState() == 2)
            new_char.insert("Check", true);
        if (ui->tableWidget_3->item(i, 0)->checkState() == 0)
            new_char.insert("Check", false);
        new_char.insert("Type", ui->tableWidget_3->item(i, 1)->text());
        if (ui->tableWidget_3->item(i, 2)->text() == "★★★★★")
            new_char.insert("Rarity", "*****");
        if (ui->tableWidget_3->item(i, 2)->text() == "★★★★")
            new_char.insert("Rarity", "****");
        if (ui->tableWidget_3->item(i, 2)->text() == "★★★")
            new_char.insert("Rarity", "***");
        new_char.insert("Phase", ui->tableWidget_3->item(i, 3)->text());
        new_char.insert("Current level", ui->tableWidget_3->item(i, 4)->text());
        new_char.insert("Target level", ui->tableWidget_3->item(i, 5)->text());
        jsonArray.append(new_char);
    }

    jsonObject.insert("weapon_training", jsonArray);
    jsonResponse.setObject(jsonObject);
    file.open(QIODevice::ReadWrite | QIODevice::Text| QFile::Truncate);
    file.write(jsonResponse.toJson());
    file.close();

    update_weapon_training_list();
    calculate();
}


void genshin_calculator::on_listWidget_8_itemSelectionChanged()
{
    QString val;
    QFile file;
    file.setFileName(filepath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject jsonObject = jsonResponse.object();
    QJsonArray jsonArray = jsonObject["weapons"].toArray();
    QJsonObject tmp;
    tmp = jsonArray.at(ui->listWidget_8->currentRow()).toObject();
    ui->lineEdit_2->setText(tmp["Name"].toString());
    ui->comboBox_11->setCurrentIndex(ui->comboBox_11->findText(tmp["Type"].toString()));
    if (tmp["Rarity"] == "*****")
        ui->comboBox_8->setCurrentIndex(ui->comboBox_8->findText("★★★★★"));
    if (tmp["Rarity"] == "****")
        ui->comboBox_8->setCurrentIndex(ui->comboBox_8->findText("★★★★"));
    if (tmp["Rarity"] == "***")
        ui->comboBox_8->setCurrentIndex(ui->comboBox_8->findText("★★★"));
    ui->comboBox_12->setCurrentIndex(ui->comboBox_12->findText(tmp["Weapon material"].toString()));
    ui->comboBox_10->setCurrentIndex(ui->comboBox_10->findText(tmp["Elite material"].toString()));
    ui->comboBox_9->setCurrentIndex(ui->comboBox_9->findText(tmp["Common material"].toString()));
}


void genshin_calculator::on_pushButton_5_clicked()
{
    if(ui->listWidget_7->count() > 0){
        QString val;
        QFile file;
        file.setFileName(filepath);
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        val = file.readAll();
        file.close();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(val.toUtf8());
        QJsonObject jsonObject = jsonResponse.object();
        QJsonArray jsonArray = jsonObject["weapons"].toArray();
        QJsonArray jsonArray_2 = jsonObject["weapon_training"].toArray();

        QJsonObject new_char;
        new_char.insert("Name", ui->lineEdit_2->text());
        new_char.insert("Type", ui->comboBox_11->currentText());
        if (ui->comboBox_8->currentText() == "★★★★★")
            new_char.insert("Rarity", "*****");
        if (ui->comboBox_8->currentText() == "★★★★")
            new_char.insert("Rarity", "****");
        if (ui->comboBox_8->currentText() == "★★★")
            new_char.insert("Rarity", "***");
        new_char.insert("Weapon material", ui->comboBox_12->currentText());
        new_char.insert("Elite material", ui->comboBox_10->currentText());
        new_char.insert("Common material", ui->comboBox_9->currentText());
        jsonArray.replace(ui->listWidget_8->currentRow(), new_char);
        jsonObject.insert("weapons", jsonArray);


        QJsonObject tmp = jsonArray_2.at(ui->listWidget_8->currentRow()).toObject();
        tmp.insert("Name", ui->lineEdit_2->text());
        jsonArray_2.replace(ui->listWidget_8->currentRow(), tmp);
        jsonObject.insert("weapon_training", jsonArray_2);

        jsonResponse.setObject(jsonObject);
        file.open(QIODevice::ReadWrite | QIODevice::Text| QFile::Truncate);
        file.write(jsonResponse.toJson());
        file.close();

        ui->lineEdit_2->clear();
        update_weapon_list();
    }
}

