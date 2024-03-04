#include "add_atoms_formula_form.h"
#include "ui_add_atoms_formula_form.h"

Add_atoms_formula_form::Add_atoms_formula_form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Add_atoms_formula_form)
{

    ui->setupUi(this);

    if (this->objectName().isEmpty())
        this->setObjectName(QString::fromUtf8("Form"));
    this->resize(377, 232);

    name_label = new QLabel(this);
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


    this->setWindowTitle(QCoreApplication::translate("Form", "Add_atoms_formula", nullptr));
    name_label->setText(QCoreApplication::translate("Form", "Pn(x,A) = (X E A)", nullptr));
    add_button->setText(QCoreApplication::translate("Form", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
    cancel_button->setText(QCoreApplication::translate("Form", "\320\236\321\202\320\274\320\265\320\275\320\260", nullptr));
    left_label->setText(QCoreApplication::translate("Form", "P (", nullptr));
    right_label->setText(QCoreApplication::translate("Form", ")", nullptr));

    QMetaObject::connectSlotsByName(this);

}

Add_atoms_formula_form::~Add_atoms_formula_form()
{
    delete ui;
}
