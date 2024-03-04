#include "build_formula_form.h"
#include "ui_build_formula_form.h"

Build_formula_form::Build_formula_form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Build_formula_form)
{
    ui->setupUi(this);
}

Build_formula_form::~Build_formula_form()
{
    delete ui;
}
