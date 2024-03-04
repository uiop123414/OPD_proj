#include "swap_form.h"
#include "ui_swap_form.h"

Swap_form::Swap_form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Swap_form)
{
    ui->setupUi(this);
}

Swap_form::~Swap_form()
{
    delete ui;
}
