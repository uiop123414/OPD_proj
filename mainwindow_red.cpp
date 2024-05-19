#include "mainwindow_red.h"
#include "ui_mainwindow_red.h"

#include <string>
#include <locale>
#include <codecvt>
#include <iostream>
#include <QString>
#include <QDebug>
#include <QFile>
#include <QDir>

mainwindow_red::mainwindow_red(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainwindow_red)
{
    ui->setupUi(this);

    //ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    for(int i=1; i<5; i++){
        ui->tableWidget->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
//        ui->tableWidget->verticalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
    }

    ui_AAF = new Add_atoms_formula_form();
    ui_NKF = new Or_fun_form();
    ui_NDF = new Or_fun_form();
    ui_NNF = new Or_fun_form();

    ui_ACF = new Or_fun_form();
    ui_ECF = new Or_fun_form();


    QObject::connect(ui->NewAtomicBtn, SIGNAL(clicked()), this, SLOT(add_atom()));

    QObject::connect(ui->NewKonBtn, SIGNAL(clicked()), this, SLOT(add_kon()));
    QObject::connect(ui->NewDizBtn, SIGNAL(clicked()), this, SLOT(add_diz()));
    QObject::connect(ui->NewNotBtn, SIGNAL(clicked()), this, SLOT(add_not()));
    QObject::connect(ui->setAnyBtn, SIGNAL(clicked()),this,SLOT(add_any()));
    QObject::connect(ui->setExistBtn, SIGNAL(clicked()),this,SLOT(add_exist()));

    //При смене комбобокса происходит загрузка транслятора из qm файла,
    //он применяется и вызывает ретранслейт тоже, ретранслейт реально вызывается,
    //но нихрена не меняет опираясь на транслятор, вопрос какого черта
    connect(ui->LangChange, static_cast<void (QComboBox::*)(const QString &)>(&QComboBox::currentIndexChanged),
            [=](const QString &str){
        bool loaded;
        loaded = mainTranslator.load(QString("mainwindow_") + str + QString(".qm"));
        qDebug() << loaded;
        qApp->removeTranslator(&mainTranslator);
        qApp->installTranslator(&mainTranslator);
        //ui->retranslateUi(this);
    });
    bool loaded;
//    QString path = QString(QDir::toNativeSeparators(QDir::currentPath() + "/mainwindow_En.qm"));
    loaded = mainTranslator.load(QString("mainwindow_Ru.qm"));
//    loaded = QFile::exists(path);
    qDebug() << loaded;
    qApp->installTranslator(&mainTranslator);
    //ui->retranslateUi(this);

    connect(ui_NKF, SIGNAL(update_values(Formula *)), this, SLOT(update_values(Formula *)));
    connect(ui_NDF, SIGNAL(update_values(Formula *)), this, SLOT(update_values(Formula *)));
    connect(ui_NNF, SIGNAL(update_values(Formula *)), this, SLOT(update_values(Formula *)));

    connect(ui_ACF, SIGNAL(update_values(Formula *)), this, SLOT(update_values(Formula *)));
    connect(ui_ECF, SIGNAL(update_values(Formula *)), this, SLOT(update_values(Formula *)));

    connect(ui_AAF, SIGNAL(sendData(EntityVariable, EntityVariable)), this, SLOT(recieveData(EntityVariable, EntityVariable)));

    Formula * formula1 = new Formula();
    tstring label1 = L"x";
    tstring label2 = L"A";
    EntityVariable ev1(label1, L"0", VARIABLE);
    EntityVariable ev2(label2, L"0", SET);

    formula1->setAtomFormula(&all_entities, ev1, ev2);

    formula1 = new Formula();
    label1 = L"x";
    label2 = L"B";
    EntityVariable ev3(label1, L"0", VARIABLE);
    EntityVariable ev4(label2, L"0", SET);

    formula1->setAtomFormula(&all_entities, ev3, ev4);

    formula1 = new Formula();
    label1 = L"x";
    label2 = L"C";
    EntityVariable ev5(label1, L"0", VARIABLE);
    EntityVariable ev6(label2, L"0", SET);

    formula1->setAtomFormula(&all_entities, ev5, ev6);


    updateTable();

}

QTableWidgetItem*  mainwindow_red::convertWideToUtf8(const wchar_t* wideString) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring wide(wideString);
    converter.to_bytes(wide);
    return new QTableWidgetItem(QString::fromStdString(converter.to_bytes(wide)));
}

void mainwindow_red::updateTable() {

    ui->tableWidget->clear();
    for(int i=0;i<all_entities.size();i++){
        // Вставляем строку
        ui->tableWidget->insertRow(i);
        /* Устанавливаем в первую колонку id забирая его из результата SQL-запроса
         * Эта колонка будет скрыта
         * */
        ui->tableWidget->setItem(i,0, new QTableWidgetItem(QString::number(i+1)));

        QString res;
        // Устанавливаем чекбокс во вторую колонку
        ui->tableWidget->setItem(i,1, convertWideToUtf8(all_entities[i]->getText().data()));

        Formula * icurr = (Formula *)all_entities[i];

        if (icurr->getFeature() == PERFORMED_FEATURE)
            res = "выполнимая";
        else if (icurr->getFeature() == TRUTH_FEATURE)
            res = "истинная";
        else if (icurr->getFeature() == FALSE_FEATURE)
            res = "ложная";
        else if (icurr->getFeature() == ATOMARN_FEATURE)
            res = "атомарная";

        // Далее забираем все данные из результата запроса и устанавливаем в остальные поля
        ui->tableWidget->setItem(i,2, new QTableWidgetItem(res));
//        ui->tableWidget->setItem(i,3, new QTableWidgetItem(query.value(3).toString()));
//        ui->tableWidget->setItem(i,4, new QTableWidgetItem(query.value(4).toString()));
    }

}

void mainwindow_red::recieveData(EntityVariable ev1, EntityVariable ev2)
{
     Formula * formula1 = new Formula();
     formula1->setAtomFormula(&all_entities, ev1, ev2);

     updateTable();
}


void mainwindow_red::update_values(Formula * formula){

    all_entities.push_back(formula);
    std::cout<<"Hello"<<std::endl;

    updateTable();
}


void mainwindow_red::changeEvent(QEvent * event){
    if (event->type() == QEvent::LanguageChange){
        ui->retranslateUi(this);
    } else {
        QWidget::changeEvent(event);
    }
}


mainwindow_red::~mainwindow_red()
{
    delete ui;
}

void mainwindow_red::add_atom(){
//    mainTranslator.load(QString("mainwindow_En"), QString("."));
//    qApp->installTranslator(&mainTranslator);
//    ui->retranslateUi(this);
    ui_AAF->lang_upd(this->mainTranslator);
    ui_AAF->show();
};

void mainwindow_red::add_kon(){
    ui_NKF->lang_upd(this->mainTranslator);
    ui_NKF->show();
    ui_NKF->change_type(0,all_entities);
};

void mainwindow_red::add_diz(){
    ui_NDF->lang_upd(this->mainTranslator);
    ui_NDF->show();
    ui_NDF->change_type(1,all_entities);
};

void mainwindow_red::add_not(){
    ui_NNF->lang_upd(this->mainTranslator);
    ui_NNF->show();
    ui_NNF->change_type(2,all_entities);
};

void mainwindow_red::add_any(){
    ui_ACF->lang_upd(this->mainTranslator);
    ui_ACF->show();
    ui_ACF->change_type(3,all_entities);
};

void mainwindow_red::add_exist(){
    ui_ECF->lang_upd(this->mainTranslator);
    ui_ECF->show();
    ui_ECF->change_type(4,all_entities);
};
