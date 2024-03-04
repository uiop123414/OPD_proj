#ifndef ADD_ATOM_FORMULA_FORM_H
#define ADD_ATOM_FORMULA_FORM_H
#pragma once
#include <QWidget>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {class Add_atom_formula_form;}
QT_END_NAMESPACE

class Add_atom_formula_form : public QWidget
{
    Q_OBJECT
public:
    explicit Add_atom_formula_form(QWidget *parent = nullptr);

private:
    Ui::Add_atom_formula_form *ui;

    QLabel *name_label;
    QPushButton *add_button;
    QPushButton *cancel_button;
    QLabel *left_label;
    QLabel *right_label;
    QTextEdit *left_number_text_line;
    QTextEdit *right_number_text_line;
    QTextEdit *right_letter_text_line;
    QTextEdit *left_letter_text_line;

};

#endif // ADD_ATOM_FORMULA_FORM_H
