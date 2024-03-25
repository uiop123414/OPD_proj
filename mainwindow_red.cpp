#include "mainwindow_red.h"
#include "ui_mainwindow_red.h"

mainwindow_red::mainwindow_red(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainwindow_red)
{
    ui->setupUi(this);
}

mainwindow_red::~mainwindow_red()
{
    delete ui;
}
