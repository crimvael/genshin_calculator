#include "genshin_calculator.h"
#include "ui_genshin_calculator.h"
#include "QJsonDocument"
#include "QJsonObject"
#include "QJsonArray"
#include "QFile"


genshin_calculator::genshin_calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::genshin_calculator)
{
    ui->setupUi(this);
}

genshin_calculator::~genshin_calculator()
{
    delete ui;
}

void genshin_calculator::on_pushButton_7_clicked()
{

    QString val;
    QFile file;
    file.setFileName("C:/Users/Oscar/Desktop/genshin_calculator/database.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject jsonObject = jsonResponse.object();
    QJsonArray jsonArray = jsonObject["common_materials"].toArray();
    for (int i = 0; i<jsonArray.size(); i++)
        ui->listWidget->addItem(jsonArray[i].toString());

    //QJsonValueRef ref = jsonObject.find("common_materials").value();
    //QJsonObject m_addvalue = ref.toObject();
    jsonArray.append("india");
    //jsonArray.push_back(jsonObject);
    jsonObject.insert("common_materials", jsonArray);
    //ref=m_addvalue;
    jsonResponse.setObject(jsonObject);
    file.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
    file.write(jsonResponse.toJson());
    file.close();

   /*
    QFile file(filepath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QJsonParseError JsonParseError;
    QJsonDocument JsonDocument = QJsonDocument::fromJson(file.readAll(), &JsonParseError);
    file.close();
    QJsonObject RootObject = JsonDocument.object();
    QJsonValueRef ref = RootObject.find("Address").value();
    QJsonObject m_addvalue = ref.toObject();
    m_addvalue.insert("Street","India");//set the value you want to modify
    ref=m_addvalue; //assign the modified object to reference
    JsonDocument.setObject(RootObject); // set to json document
    file.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
    file.write(JsonDocument.toJson());
    file.close();
    {"common_materials" : ["Slime", "Mask", "Arrow"]}
    */


    if (!ui->lineEdit_8->text().isEmpty())
        ui->listWidget->addItem(ui->lineEdit_8->text());

    ui->lineEdit_8->clear();
}


void genshin_calculator::on_pushButton_8_clicked()
{
    qDeleteAll(ui->listWidget->selectedItems());
}


void genshin_calculator::on_pushButton_9_clicked()
{
    if (!ui->lineEdit_10->text().isEmpty())
        ui->listWidget_2->addItem(ui->lineEdit_10->text());

    ui->lineEdit_10->clear();
}


void genshin_calculator::on_pushButton_10_clicked()
{
    qDeleteAll(ui->listWidget_2->selectedItems());
}


void genshin_calculator::on_pushButton_11_clicked()
{
    if (!ui->lineEdit_11->text().isEmpty())
        ui->listWidget_3->addItem(ui->lineEdit_11->text());

    ui->lineEdit_11->clear();
}


void genshin_calculator::on_pushButton_12_clicked()
{
    qDeleteAll(ui->listWidget_3->selectedItems());
}


void genshin_calculator::on_pushButton_13_clicked()
{
    if (!ui->lineEdit_9->text().isEmpty())
        ui->listWidget_4->addItem(ui->lineEdit_9->text());

    ui->lineEdit_9->clear();
}


void genshin_calculator::on_pushButton_14_clicked()
{
    qDeleteAll(ui->listWidget_4->selectedItems());
}


void genshin_calculator::on_pushButton_15_clicked()
{
    if (!ui->lineEdit_12->text().isEmpty())
        ui->listWidget_5->addItem(ui->lineEdit_12->text());

    ui->lineEdit_12->clear();
}


void genshin_calculator::on_pushButton_16_clicked()
{
    qDeleteAll(ui->listWidget_5->selectedItems());
}


void genshin_calculator::on_pushButton_17_clicked()
{
    if (!ui->lineEdit_13->text().isEmpty())
        ui->listWidget_6->addItem(ui->lineEdit_13->text());

    ui->lineEdit_13->clear();
}


void genshin_calculator::on_pushButton_18_clicked()
{
    qDeleteAll(ui->listWidget_6->selectedItems());
}
