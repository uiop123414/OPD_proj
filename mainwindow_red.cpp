#include "mainwindow_red.h"
#include "ui_mainwindow_red.h"




mainwindow_red::mainwindow_red(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainwindow_red)
{
    ui->setupUi(this);


    ui_AAF = new Add_atoms_formula_form();


    QObject::connect(ui->NewAtomicBtn, SIGNAL(clicked()), this, SLOT(add_atom()));
}

mainwindow_red::~mainwindow_red()
{
    delete ui;
}

void mainwindow_red::add_atom(){
    ui_AAF->show();

};
