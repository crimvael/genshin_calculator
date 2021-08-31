#include "genshin_calculator.h"
#include "ui_genshin_calculator.h"
#include "QJsonDocument"
#include "QJsonObject"
#include "QJsonArray"
#include "QFile"
#include "QStringList"

extern QString filepath;
QString filepath = "C:/Users/Oscar/Desktop/genshin_calculator/database.json";

genshin_calculator::genshin_calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::genshin_calculator)
{
    ui->setupUi(this);
    update_comboboxes();
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_2->horizontalHeader()->setStretchLastSection(true);
    QString val;
    QFile file;
    file.setFileName(filepath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject jsonObject = jsonResponse.object();
    update_char_list(jsonObject);
}

genshin_calculator::~genshin_calculator()
{
    delete ui;
}

void genshin_calculator::update_char_list(QJsonObject obj){

    ui->listWidget_7->clear();
    ui->tableWidget_2->setRowCount(0);
    ui->tableWidget->setRowCount(0);
    QJsonObject tmp;
    QJsonArray jsonArray = obj["training"].toArray();
    QJsonArray array = obj["characters"].toArray();
    for (int i = 0; i<array.size(); i++){
        tmp = array.at(i).toObject();
        ui->listWidget_7->addItem(tmp["Name"].toString());
        ui->tableWidget_2->insertRow(ui->tableWidget_2->rowCount());
        ui->tableWidget_2->setItem(ui->tableWidget_2->rowCount()-1, 0, new QTableWidgetItem(tmp["Name"].toString()));
        ui->tableWidget_2->setItem(ui->tableWidget_2->rowCount()-1, 1, new QTableWidgetItem(tmp["Vision"].toString()));
        ui->tableWidget_2->setItem(ui->tableWidget_2->rowCount()-1, 2, new QTableWidgetItem(tmp["Region"].toString()));
        ui->tableWidget_2->setItem(ui->tableWidget_2->rowCount()-1, 3, new QTableWidgetItem(tmp["Common material"].toString()));
        ui->tableWidget_2->setItem(ui->tableWidget_2->rowCount()-1, 4, new QTableWidgetItem(tmp["Ascension material"].toString()));
        ui->tableWidget_2->setItem(ui->tableWidget_2->rowCount()-1, 5, new QTableWidgetItem(tmp["Local speciality"].toString()));
        ui->tableWidget_2->setItem(ui->tableWidget_2->rowCount()-1, 6, new QTableWidgetItem(tmp["Talent material"].toString()));
        ui->tableWidget_2->setItem(ui->tableWidget_2->rowCount()-1, 7, new QTableWidgetItem(tmp["Weekly material"].toString()));
    }
    for (int i = 0; i<jsonArray.size(); i++){
        tmp = jsonArray.at(i).toObject();
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        QTableWidgetItem *item = new QTableWidgetItem(tmp["Name"].toString());
        if (tmp["Checked"].toBool())
            item->setCheckState(Qt::Checked);
        else
            item->setCheckState(Qt::Unchecked);
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0, item);
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1, new QTableWidgetItem(tmp["Current lvl"].toString()));

    }
}

void genshin_calculator::update_comboboxes(){

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
    QJsonArray jsonArray_8 = jsonObject["characters"].toArray();
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
    }
    for (int i = 0; i<jsonArray_2.size(); i++){
        ui->listWidget_2->addItem(jsonArray_2[i].toString());
        ui->comboBox_4->addItem(jsonArray_2[i].toString());
    }
    for (int i = 0; i<jsonArray_3.size(); i++){
        ui->listWidget_3->addItem(jsonArray_3[i].toString());
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
    }
}

// add common material
void genshin_calculator::on_pushButton_7_clicked()
{
    if (!ui->lineEdit_8->text().isEmpty()){

        QString val;
        QFile file;
        file.setFileName(filepath);
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        val = file.readAll();
        file.close();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(val.toUtf8());
        QJsonObject jsonObject = jsonResponse.object();
        QJsonArray jsonArray = jsonObject["common_materials"].toArray();
        jsonArray.append(ui->lineEdit_8->text());
        jsonObject.insert("common_materials", jsonArray);
        jsonResponse.setObject(jsonObject);
        file.open(QIODevice::ReadWrite | QIODevice::Text| QFile::Truncate);
        file.write(jsonResponse.toJson());
        file.close();

        ui->lineEdit_8->clear();
    }

    update_comboboxes();
}

// remove common material
void genshin_calculator::on_pushButton_8_clicked()
{
    QString val;
    QFile file;
    file.setFileName(filepath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject jsonObject = jsonResponse.object();
    QJsonArray jsonArray = jsonObject["common_materials"].toArray();
    jsonArray.removeAt(ui->listWidget->currentRow());
    jsonObject.insert("common_materials", jsonArray);
    jsonResponse.setObject(jsonObject);
    file.open(QIODevice::ReadWrite | QIODevice::Text | QFile::Truncate);
    file.write(jsonResponse.toJson());
    file.close();

    update_comboboxes();
}

// add ascension material
void genshin_calculator::on_pushButton_9_clicked()
{
    if (!ui->lineEdit_10->text().isEmpty()){

        QString val;
        QFile file;
        file.setFileName(filepath);
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        val = file.readAll();
        file.close();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(val.toUtf8());
        QJsonObject jsonObject = jsonResponse.object();
        QJsonArray jsonArray = jsonObject["ascension_materials"].toArray();
        jsonArray.append(ui->lineEdit_10->text());
        jsonObject.insert("ascension_materials", jsonArray);
        jsonResponse.setObject(jsonObject);
        file.open(QIODevice::ReadWrite | QIODevice::Text| QFile::Truncate);
        file.write(jsonResponse.toJson());
        file.close();

        ui->lineEdit_10->clear();
    }

    update_comboboxes();
}

// remove ascension material
void genshin_calculator::on_pushButton_10_clicked()
{
    QString val;
    QFile file;
    file.setFileName(filepath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject jsonObject = jsonResponse.object();
    QJsonArray jsonArray = jsonObject["ascension_materials"].toArray();
    jsonArray.removeAt(ui->listWidget_2->currentRow());
    jsonObject.insert("ascension_materials", jsonArray);
    jsonResponse.setObject(jsonObject);
    file.open(QIODevice::ReadWrite | QIODevice::Text | QFile::Truncate);
    file.write(jsonResponse.toJson());
    file.close();

    update_comboboxes();
}

// add elite material
void genshin_calculator::on_pushButton_11_clicked()
{
    if (!ui->lineEdit_11->text().isEmpty()){

        QString val;
        QFile file;
        file.setFileName(filepath);
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        val = file.readAll();
        file.close();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(val.toUtf8());
        QJsonObject jsonObject = jsonResponse.object();
        QJsonArray jsonArray = jsonObject["elite_materials"].toArray();
        jsonArray.append(ui->lineEdit_11->text());
        jsonObject.insert("elite_materials", jsonArray);
        jsonResponse.setObject(jsonObject);
        file.open(QIODevice::ReadWrite | QIODevice::Text| QFile::Truncate);
        file.write(jsonResponse.toJson());
        file.close();

        ui->lineEdit_11->clear();
    }

    update_comboboxes();
}

// remove elite material
void genshin_calculator::on_pushButton_12_clicked()
{
    QString val;
    QFile file;
    file.setFileName(filepath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject jsonObject = jsonResponse.object();
    QJsonArray jsonArray = jsonObject["elite_materials"].toArray();
    jsonArray.removeAt(ui->listWidget_3->currentRow());
    jsonObject.insert("elite_materials", jsonArray);
    jsonResponse.setObject(jsonObject);
    file.open(QIODevice::ReadWrite | QIODevice::Text | QFile::Truncate);
    file.write(jsonResponse.toJson());
    file.close();

    update_comboboxes();
}

// add weapon ascension material
void genshin_calculator::on_pushButton_24_clicked()
{
    if (!ui->lineEdit_14->text().isEmpty()){

        QString val;
        QFile file;
        file.setFileName(filepath);
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        val = file.readAll();
        file.close();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(val.toUtf8());
        QJsonObject jsonObject = jsonResponse.object();
        QJsonArray jsonArray = jsonObject["weapon_materials"].toArray();
        jsonArray.append(ui->lineEdit_14->text());
        jsonObject.insert("weapon_materials", jsonArray);
        jsonResponse.setObject(jsonObject);
        file.open(QIODevice::ReadWrite | QIODevice::Text| QFile::Truncate);
        file.write(jsonResponse.toJson());
        file.close();

        ui->lineEdit_14->clear();
    }

    update_comboboxes();
}

// remove weapon ascension material
void genshin_calculator::on_pushButton_23_clicked()
{
    QString val;
    QFile file;
    file.setFileName(filepath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject jsonObject = jsonResponse.object();
    QJsonArray jsonArray = jsonObject["weapon_materials"].toArray();
    jsonArray.removeAt(ui->listWidget_9->currentRow());
    jsonObject.insert("weapon_materials", jsonArray);
    jsonResponse.setObject(jsonObject);
    file.open(QIODevice::ReadWrite | QIODevice::Text | QFile::Truncate);
    file.write(jsonResponse.toJson());
    file.close();

    update_comboboxes();
}

// add local speciality
void genshin_calculator::on_pushButton_13_clicked()
{
    if (!ui->lineEdit_9->text().isEmpty()){

        QString val;
        QFile file;
        file.setFileName(filepath);
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        val = file.readAll();
        file.close();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(val.toUtf8());
        QJsonObject jsonObject = jsonResponse.object();
        QJsonArray jsonArray = jsonObject["local_materials"].toArray();
        jsonArray.append(ui->lineEdit_9->text());
        jsonObject.insert("local_materials", jsonArray);
        jsonResponse.setObject(jsonObject);
        file.open(QIODevice::ReadWrite | QIODevice::Text| QFile::Truncate);
        file.write(jsonResponse.toJson());
        file.close();

        ui->lineEdit_9->clear();
    }

    update_comboboxes();
}

// remove local speciality
void genshin_calculator::on_pushButton_14_clicked()
{
    QString val;
    QFile file;
    file.setFileName(filepath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject jsonObject = jsonResponse.object();
    QJsonArray jsonArray = jsonObject["local_materials"].toArray();
    jsonArray.removeAt(ui->listWidget_4->currentRow());
    jsonObject.insert("local_materials", jsonArray);
    jsonResponse.setObject(jsonObject);
    file.open(QIODevice::ReadWrite | QIODevice::Text | QFile::Truncate);
    file.write(jsonResponse.toJson());
    file.close();

    update_comboboxes();
}

// add talent material
void genshin_calculator::on_pushButton_15_clicked()
{
    if (!ui->lineEdit_12->text().isEmpty()){

        QString val;
        QFile file;
        file.setFileName(filepath);
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        val = file.readAll();
        file.close();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(val.toUtf8());
        QJsonObject jsonObject = jsonResponse.object();
        QJsonArray jsonArray = jsonObject["talent_materials"].toArray();
        jsonArray.append(ui->lineEdit_12->text());
        jsonObject.insert("talent_materials", jsonArray);
        jsonResponse.setObject(jsonObject);
        file.open(QIODevice::ReadWrite | QIODevice::Text| QFile::Truncate);
        file.write(jsonResponse.toJson());
        file.close();

        ui->lineEdit_12->clear();
    }

    update_comboboxes();
}

// remove talent materia
void genshin_calculator::on_pushButton_16_clicked()
{
    QString val;
    QFile file;
    file.setFileName(filepath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject jsonObject = jsonResponse.object();
    QJsonArray jsonArray = jsonObject["talent_materials"].toArray();
    jsonArray.removeAt(ui->listWidget_5->currentRow());
    jsonObject.insert("talent_materials", jsonArray);
    jsonResponse.setObject(jsonObject);
    file.open(QIODevice::ReadWrite | QIODevice::Text | QFile::Truncate);
    file.write(jsonResponse.toJson());
    file.close();

    update_comboboxes();
}

//add weekly material
void genshin_calculator::on_pushButton_17_clicked()
{
    if (!ui->lineEdit_13->text().isEmpty()){

        QString val;
        QFile file;
        file.setFileName(filepath);
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        val = file.readAll();
        file.close();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(val.toUtf8());
        QJsonObject jsonObject = jsonResponse.object();
        QJsonArray jsonArray = jsonObject["weekly_materials"].toArray();
        jsonArray.append(ui->lineEdit_13->text());
        jsonObject.insert("weekly_materials", jsonArray);
        jsonResponse.setObject(jsonObject);
        file.open(QIODevice::ReadWrite | QIODevice::Text| QFile::Truncate);
        file.write(jsonResponse.toJson());
        file.close();

        ui->lineEdit_13->clear();
    }

    update_comboboxes();
}

// remove weekly material
void genshin_calculator::on_pushButton_18_clicked()
{
    QString val;
    QFile file;
    file.setFileName(filepath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject jsonObject = jsonResponse.object();
    QJsonArray jsonArray = jsonObject["weekly_materials"].toArray();
    jsonArray.removeAt(ui->listWidget_6->currentRow());
    jsonObject.insert("weekly_materials", jsonArray);
    jsonResponse.setObject(jsonObject);
    file.open(QIODevice::ReadWrite | QIODevice::Text | QFile::Truncate);
    file.write(jsonResponse.toJson());
    file.close();

    update_comboboxes();
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
        new_char.insert("Name", ui->lineEdit->text());
        new_char.insert("Check", 0);
        new_char.insert("Current level", 1);
        new_char.insert("Target level", 90);
        new_char.insert("Normal attack lvl", 1);
        new_char.insert("Normal attack target level", 8);
        new_char.insert("Elemental skill lvl", 1);
        new_char.insert("Elemental skill target lvl", 8);
        new_char.insert("Elemental burst lvl", 1);
        new_char.insert("Elemental burst target lvl", 8);
        jsonArray_2.append(new_char);
        jsonObject.insert("training", jsonArray_2);

        jsonResponse.setObject(jsonObject);
        file.open(QIODevice::ReadWrite | QIODevice::Text| QFile::Truncate);
        file.write(jsonResponse.toJson());
        file.close();

        ui->lineEdit->clear();
        update_char_list(jsonObject);
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
    update_char_list(jsonObject);
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
        update_char_list(jsonObject);
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
