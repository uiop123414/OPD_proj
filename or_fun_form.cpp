#include "or_fun_form.h"
#include "ui_or_fun_form.h"

#include <QString>
Or_fun_form::Or_fun_form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Or_fun_form)
{
    ui->setupUi(this);

    if (this->objectName().isEmpty())
        this->setObjectName(QString::fromUtf8("Form"));


    QObject::connect(ui->OkBtn, SIGNAL(clicked()), this, SLOT(new_accept()));

//    this->resize(800, 600);
//    name_label = new QLabel(this);
//    name_label->setObjectName(QString::fromUtf8("name_label"));
//    name_label->setGeometry(QRect(20, 20, 181, 18));
//    left_listView = new QListView(this);
//    left_listView->setObjectName(QString::fromUtf8("left_listView"));
//    left_listView->setGeometry(QRect(0, 100, 321, 461));
//    force_right_Button = new QPushButton(this);
//    force_right_Button->setObjectName(QString::fromUtf8("force_right_Button"));
//    force_right_Button->setGeometry(QRect(350, 70, 31, 26));
//    right_Button = new QPushButton(this);
//    right_Button->setObjectName(QString::fromUtf8("right_Button"));
//    right_Button->setGeometry(QRect(350, 100, 31, 26));
//    left_Button = new QPushButton(this);
//    left_Button->setObjectName(QString::fromUtf8("left_Button"));
//    left_Button->setGeometry(QRect(350, 130, 31, 26));
//    force_left_Button = new QPushButton(this);
//    force_left_Button->setObjectName(QString::fromUtf8("force_left_Button"));
//    force_left_Button->setGeometry(QRect(350, 160, 31, 26));
//    upper_listView = new QListView(this);
//    upper_listView->setObjectName(QString::fromUtf8("upper_listView"));
//    upper_listView->setGeometry(QRect(410, 50, 381, 241));
//    to_all_formulas_radioButton = new QRadioButton(this);
//    to_all_formulas_radioButton->setObjectName(QString::fromUtf8("to_all_formulas_radioButton"));
//    to_all_formulas_radioButton->setGeometry(QRect(20, 50, 291, 24));
//    bin_radioButton = new QRadioButton(this);
//    bin_radioButton->setObjectName(QString::fromUtf8("bin_radioButton"));
//    bin_radioButton->setGeometry(QRect(20, 70, 102, 24));
//    low_listView = new QListView(this);
//    low_listView->setObjectName(QString::fromUtf8("low_listView"));
//    low_listView->setGeometry(QRect(410, 320, 381, 241));
//    perform_to_all_list_radioButton = new QRadioButton(this);
//    perform_to_all_list_radioButton->setObjectName(QString::fromUtf8("perform_to_all_list_radioButton"));
//    perform_to_all_list_radioButton->setGeometry(QRect(410, 293, 271, 31));
//    perform_Button = new QPushButton(this);
//    perform_Button->setObjectName(QString::fromUtf8("perform_Button"));
//    perform_Button->setGeometry(QRect(610, 570, 80, 26));
//    cancel_Button = new QPushButton(this);
//    cancel_Button->setObjectName(QString::fromUtf8("cancel_Button"));
//    cancel_Button->setGeometry(QRect(710, 570, 80, 26));

//    this->setWindowTitle(QCoreApplication::translate("Form", "Form", nullptr));
//    name_label->setText(QCoreApplication::translate("Form", "\320\236\320\277\320\265\321\200\320\260\321\206\320\270\321\217 \320\276\320\261\321\212\320\265\320\264\320\270\320\275\320\265\320\275\320\270\321\217 V", nullptr));
//    force_right_Button->setText(QCoreApplication::translate("Form", ">>", nullptr));
//    right_Button->setText(QCoreApplication::translate("Form", ">", nullptr));
//    left_Button->setText(QCoreApplication::translate("Form", "<", nullptr));
//    force_left_Button->setText(QCoreApplication::translate("Form", "<<", nullptr));
//    to_all_formulas_radioButton->setText(QCoreApplication::translate("Form", "\320\237\321\200\320\270\320\274\320\265\320\275\320\270\321\202\321\214 \320\276\320\277\320\265\321\200\320\260\321\206\320\270\321\216 \320\272\320\276 \320\262\321\201\320\265\320\274 \321\204\320\276\321\200\320\274\321\203\320\273\320\260\320\274", nullptr));
//    bin_radioButton->setText(QCoreApplication::translate("Form", "\320\221\320\270\320\275\320\260\321\200\320\275\320\260\321\217", nullptr));
//    perform_to_all_list_radioButton->setText(QCoreApplication::translate("Form", "\320\237\321\200\320\270\320\274\320\265\320\275\321\217\321\202\321\214 \320\276\320\277\320\265\321\200\320\260\321\206\320\270\321\216 \320\272\320\276 \320\262\321\201\320\265\320\274\321\203 \321\201\320\277\320\270\321\201\320\272\321\203", nullptr));
//    perform_Button->setText(QCoreApplication::translate("Form", "\320\222\321\213\320\277\320\276\320\273\320\275\320\270\321\202\321\214", nullptr));
//    cancel_Button->setText(QCoreApplication::translate("Form", "\320\236\321\202\320\274\320\265\320\275\320\260", nullptr));

//    QMetaObject::connectSlotsByName(this);
}

Or_fun_form::~Or_fun_form()
{
    delete ui;
}

void Or_fun_form::new_accept()
{
    this->close();
}

void Or_fun_form::change_type(int new_type,vector <EntityBase *> _all_entities)
{
    this->type=new_type;
    this->all_entities = _all_entities;
    all_entities[0]->getText().data();
    for(int i=0;i<this->all_entities.size();i++){

        auto res = QString::fromStdWString(all_entities[i]->getText().data()).toStdString().c_str();
        QListWidgetItem *___qlistwidgetitem = ui->ExistedFormulas->item(i);
                ___qlistwidgetitem->setText(QCoreApplication::translate("Or_fun_form", res, nullptr));
    }

    switch (this->type){
    case 0:
        this->setWindowTitle(QCoreApplication::translate("Create AND formula", "Create AND formula", nullptr));
        break;
    case 1:
        this->setWindowTitle(QString("Create OR formula"));
        break;
    case 2:
        this->setWindowTitle(QCoreApplication::translate("Create NOT formula", "Create NOT formula", nullptr));
        break;
    default:
        this->setWindowTitle(QString("ne robit!!"));
        break;
    }
}
