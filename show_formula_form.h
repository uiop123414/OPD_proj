#ifndef SHOW_FORMULA_FORM_H
#define SHOW_FORMULA_FORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

namespace Ui {
class Show_formula_form;
}

class Show_formula_form : public QWidget
{
    Q_OBJECT

public:
    explicit Show_formula_form(QWidget *parent = nullptr);
    ~Show_formula_form();

private:
    QTableView *data_table;
    QPushButton *change_button;
    QPushButton *ok_button;
    QPushButton *cancel_button;


    Ui::Show_formula_form *ui;
};

#endif // SHOW_FORMULA_FORM_H
