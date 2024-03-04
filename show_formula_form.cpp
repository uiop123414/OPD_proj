#include "show_formula_form.h"
#include "ui_show_formula_form.h"

Show_formula_form::Show_formula_form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Show_formula_form)
{
    ui->setupUi(this);

    if (this->objectName().isEmpty())
        this->setObjectName(QString::fromUtf8("Form"));
    this->resize(400, 300);
    data_table = new QTableView(this);
    data_table->setObjectName(QString::fromUtf8("data_table"));
    data_table->setGeometry(QRect(10, 30, 381, 221));
    change_button = new QPushButton(this);
    change_button->setObjectName(QString::fromUtf8("change_button"));
    change_button->setGeometry(QRect(89, 260, 121, 26));
    ok_button = new QPushButton(this);
    ok_button->setObjectName(QString::fromUtf8("ok_button"));
    ok_button->setGeometry(QRect(220, 260, 80, 26));
    cancel_button = new QPushButton(this);
    cancel_button->setObjectName(QString::fromUtf8("cancel_button"));
    cancel_button->setGeometry(QRect(310, 260, 80, 26));

    this->setWindowTitle(QCoreApplication::translate("Form", "Form", nullptr));
    change_button->setText(QCoreApplication::translate("Form", "\320\237\321\200\320\265\320\276\320\261\321\200\320\260\320\267\320\276\320\262\320\260\320\275\320\270\320\265", nullptr));
    ok_button->setText(QCoreApplication::translate("Form", "\320\236\320\232", nullptr));
    cancel_button->setText(QCoreApplication::translate("Form", "\320\236\321\202\320\274\320\265\320\275\320\260", nullptr));

    QMetaObject::connectSlotsByName(this);

}

Show_formula_form::~Show_formula_form()
{
    delete ui;
}
