#include "genshin_calculator.h"
#include "ui_genshin_calculator.h"
#include "QJsonDocument"
#include "QJsonObject"
#include "QJsonArray"
#include "QFile"

extern QString filepath;
QString filepath = "C:/Users/Oscar/Desktop/genshin_calculator/database.json";

genshin_calculator::genshin_calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::genshin_calculator)
{
    ui->setupUi(this);
    update_comboboxes();
    QString val;
    QFile file;
    file.setFileName(filepath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject jsonObject = jsonResponse.object();
    QJsonArray jsonArray_7 = jsonObject["characters"].toArray();
    QJsonObject tmp;
    for (int i = 0; i<jsonArray_7.size(); i++){
        tmp = jsonArray_7.at(i).toObject();
        ui->listWidget_7->addItem(tmp["Name"].toString());
    }
}

genshin_calculator::~genshin_calculator()
{
    delete ui;
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
    QJsonArray jsonArray_3 = jsonObject["weapon_materials"].toArray();
    QJsonArray jsonArray_4 = jsonObject["local_materials"].toArray();
    QJsonArray jsonArray_5 = jsonObject["talent_materials"].toArray();
    QJsonArray jsonArray_6 = jsonObject["weekly_materials"].toArray();
    QJsonObject tmp;
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
}

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

        ui->listWidget->clear();
        for (int i = 0; i<jsonArray.size(); i++)
            ui->listWidget->addItem(jsonArray[i].toString());
        ui->lineEdit_8->clear();
    }

    update_comboboxes();
}


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
    ui->listWidget->clear();

    for (int i = 0; i<jsonArray.size(); i++)
        ui->listWidget->addItem(jsonArray[i].toString());

    update_comboboxes();
}


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

        ui->listWidget_2->clear();
        for (int i = 0; i<jsonArray.size(); i++)
            ui->listWidget_2->addItem(jsonArray[i].toString());
        ui->lineEdit_10->clear();
    }

    update_comboboxes();
}


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
    ui->listWidget_2->clear();

    for (int i = 0; i<jsonArray.size(); i++)
        ui->listWidget_2->addItem(jsonArray[i].toString());

    update_comboboxes();
}


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
        QJsonArray jsonArray = jsonObject["weapon_materials"].toArray();
        jsonArray.append(ui->lineEdit_11->text());
        jsonObject.insert("weapon_materials", jsonArray);
        jsonResponse.setObject(jsonObject);
        file.open(QIODevice::ReadWrite | QIODevice::Text| QFile::Truncate);
        file.write(jsonResponse.toJson());
        file.close();

        ui->listWidget_3->clear();
        for (int i = 0; i<jsonArray.size(); i++)
            ui->listWidget_3->addItem(jsonArray[i].toString());
        ui->lineEdit_11->clear();
    }

    update_comboboxes();
}


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
    QJsonArray jsonArray = jsonObject["weapon_materials"].toArray();
    jsonArray.removeAt(ui->listWidget_3->currentRow());
    jsonObject.insert("weapon_materials", jsonArray);
    jsonResponse.setObject(jsonObject);
    file.open(QIODevice::ReadWrite | QIODevice::Text | QFile::Truncate);
    file.write(jsonResponse.toJson());
    file.close();
    ui->listWidget_3->clear();

    for (int i = 0; i<jsonArray.size(); i++)
        ui->listWidget_3->addItem(jsonArray[i].toString());

    update_comboboxes();
}


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

        ui->listWidget_4->clear();
        for (int i = 0; i<jsonArray.size(); i++)
            ui->listWidget_4->addItem(jsonArray[i].toString());
        ui->lineEdit_9->clear();
    }

    update_comboboxes();
}


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
    ui->listWidget_4->clear();

    for (int i = 0; i<jsonArray.size(); i++)
        ui->listWidget_4->addItem(jsonArray[i].toString());

    update_comboboxes();
}


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

        ui->listWidget_5->clear();
        for (int i = 0; i<jsonArray.size(); i++)
            ui->listWidget_5->addItem(jsonArray[i].toString());
        ui->lineEdit_12->clear();
    }

    update_comboboxes();
}


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
    ui->listWidget_5->clear();

    for (int i = 0; i<jsonArray.size(); i++)
        ui->listWidget_5->addItem(jsonArray[i].toString());

    update_comboboxes();
}


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

        ui->listWidget_6->clear();
        for (int i = 0; i<jsonArray.size(); i++)
            ui->listWidget_6->addItem(jsonArray[i].toString());
        ui->lineEdit_13->clear();
    }

    update_comboboxes();
}


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
    ui->listWidget_6->clear();

    for (int i = 0; i<jsonArray.size(); i++)
        ui->listWidget_6->addItem(jsonArray[i].toString());

    update_comboboxes();
}

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

        jsonResponse.setObject(jsonObject);
        file.open(QIODevice::ReadWrite | QIODevice::Text| QFile::Truncate);
        file.write(jsonResponse.toJson());
        file.close();

        ui->listWidget_7->clear();
        QJsonObject tmp;
        for (int i = 0; i<jsonArray.size(); i++){
            tmp = jsonArray.at(i).toObject();
            ui->listWidget_7->addItem(tmp["Name"].toString());
        }
        ui->lineEdit->clear();
    }
}


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
    jsonArray.removeAt(ui->listWidget_7->currentRow());
    jsonObject.insert("characters", jsonArray);
    jsonResponse.setObject(jsonObject);
    file.open(QIODevice::ReadWrite | QIODevice::Text | QFile::Truncate);
    file.write(jsonResponse.toJson());
    file.close();

    ui->listWidget_7->clear();
    QJsonObject tmp;
    for (int i = 0; i<jsonArray.size(); i++){
        tmp = jsonArray.at(i).toObject();
        ui->listWidget_7->addItem(tmp["Name"].toString());
    }
    ui->lineEdit->clear();
}


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

        jsonResponse.setObject(jsonObject);
        file.open(QIODevice::ReadWrite | QIODevice::Text| QFile::Truncate);
        file.write(jsonResponse.toJson());
        file.close();

        ui->listWidget_7->clear();
        QJsonObject tmp;
        for (int i = 0; i<jsonArray.size(); i++){
            tmp = jsonArray.at(i).toObject();
            ui->listWidget_7->addItem(tmp["Name"].toString());
        }
        ui->lineEdit->clear();
    }
}


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

