#ifndef ADD_ATOMS_FORMULA_FORM_H
#define ADD_ATOMS_FORMULA_FORM_H
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
#include <formula.h>
namespace Ui {
class Add_atoms_formula_form;
}

class Add_atoms_formula_form : public QWidget
{
    Q_OBJECT

public:
    explicit Add_atoms_formula_form(QWidget *parent = nullptr);
    ~Add_atoms_formula_form();
    void lang_upd(QTranslator &translator);

private:
    Ui::Add_atoms_formula_form *ui;
    QLabel *name_label;
    QPushButton *add_button;
    QPushButton *cancel_button;
//    QLabel *left_label;
//    QLabel *right_label;
//    QTextEdit *left_number_text_line;
//    QTextEdit *right_number_text_line;
//    QTextEdit *right_letter_text_line;
//    QTextEdit *left_letter_text_line;

 public slots:
    void atom_accept();
signals:
    void sendData(EntityVariable ev1, EntityVariable ev2);
};

#endif // ADD_ATOMS_FORMULA_FORM_H
