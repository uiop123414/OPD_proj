#include "mainwindow_red.h"
#include "ui_mainwindow_red.h"




mainwindow_red::mainwindow_red(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainwindow_red)
{
    ui->setupUi(this);


    ui_AAF = new Add_atoms_formula_form();
    ui_NKF = new Or_fun_form();
    ui_NDF = new Or_fun_form();
    ui_NNF = new Or_fun_form();


    QObject::connect(ui->NewAtomicBtn, SIGNAL(clicked()), this, SLOT(add_atom()));
    QObject::connect(ui->NewKonBtn, SIGNAL(clicked()), this, SLOT(add_kon()));
    QObject::connect(ui->NewDizBtn, SIGNAL(clicked()), this, SLOT(add_diz()));
    QObject::connect(ui->NewNotBtn, SIGNAL(clicked()), this, SLOT(add_not()));
}

mainwindow_red::~mainwindow_red()
{
    delete ui;
}

void mainwindow_red::add_atom(){
    ui_AAF->show();
};

void mainwindow_red::add_kon(){
    ui_NKF->show();
    ui_NKF->change_type(0);
};

void mainwindow_red::add_diz(){
    ui_NDF->show();
    ui_NDF->change_type(1);
};

void mainwindow_red::add_not(){
    ui_NNF->show();
    ui_NNF->change_type(2);
};
