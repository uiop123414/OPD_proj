#include "add_atom_formula_form.h"
#include "ui_add_atom_formula_form.h"

Add_atom_formula_form::Add_atom_formula_form(QWidget *parent)
    : QWidget{parent},
    ui(new Ui::Add_atom_formula_form)
{
    if (this->objectName().isEmpty())
        this->setObjectName(QString::fromUtf8("Add_atom_formula"));
    this->resize(377, 232);

    name_label->setObjectName(QString::fromUtf8("name_label"));
    name_label->setGeometry(QRect(127, 27, 101, 31));
    add_button = new QPushButton(this);
    add_button->setObjectName(QString::fromUtf8("add_button"));
    add_button->setGeometry(QRect(130, 150, 80, 26));
    cancel_button = new QPushButton(this);
    cancel_button->setObjectName(QString::fromUtf8("cancel_button"));
    cancel_button->setGeometry(QRect(230, 150, 80, 26));
    left_label = new QLabel(this);
    left_label->setObjectName(QString::fromUtf8("left_label"));
    left_label->setGeometry(QRect(70, 80, 21, 18));
    right_label = new QLabel(this);
    right_label->setObjectName(QString::fromUtf8("right_label"));
    right_label->setGeometry(QRect(250, 80, 21, 18));
    left_number_text_line = new QTextEdit(this);
    left_number_text_line->setObjectName(QString::fromUtf8("left_number_text_line"));
    left_number_text_line->setGeometry(QRect(130, 90, 31, 31));
    right_number_text_line = new QTextEdit(this);
    right_number_text_line->setObjectName(QString::fromUtf8("right_number_text_line"));
    right_number_text_line->setGeometry(QRect(210, 90, 31, 31));
    right_letter_text_line = new QTextEdit(this);
    right_letter_text_line->setObjectName(QString::fromUtf8("right_letter_text_line"));
    right_letter_text_line->setGeometry(QRect(170, 70, 31, 31));
    left_letter_text_line = new QTextEdit(this);
    left_letter_text_line->setObjectName(QString::fromUtf8("left_letter_text_line"));
    left_letter_text_line->setGeometry(QRect(90, 70, 31, 31));


    this->setWindowTitle(QCoreApplication::translate("Add_atom_formula", "Add_atom_formula", nullptr));
    name_label->setText(QCoreApplication::translate("Add_atom_formula", "Pn(x,A) = (X E A)", nullptr));
    add_button->setText(QCoreApplication::translate("Add_atom_formula", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
    cancel_button->setText(QCoreApplication::translate("Add_atom_formula", "\320\236\321\202\320\274\320\265\320\275\320\260", nullptr));
    left_label->setText(QCoreApplication::translate("Add_atom_formula", "P (", nullptr));
    right_label->setText(QCoreApplication::translate("Add_atom_formula", ")", nullptr));

    QMetaObject::connectSlotsByName(this);

}
