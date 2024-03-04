#ifndef BUILD_FORMULA_FORM_H
#define BUILD_FORMULA_FORM_H

#include <QWidget>

namespace Ui {
class Build_formula_form;
}

class Build_formula_form : public QWidget
{
    Q_OBJECT

public:
    explicit Build_formula_form(QWidget *parent = nullptr);
    ~Build_formula_form();

private:
    Ui::Build_formula_form *ui;
};

#endif // BUILD_FORMULA_FORM_H
