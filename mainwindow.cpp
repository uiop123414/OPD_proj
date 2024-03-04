#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    ui_AAF = new Add_atoms_formula_form();
    ui_SF = new Show_formula_form();
    ui_AF = new Add_fun_form();
    ui_OF = new Or_fun_form();
    ui_NF = new Not_fun_form();
    ui_ACF = new Any_creation_fun_form();
    ui_EF = new Exist_fun_form();
    ui_SWF = new Swap_form();
    ui_BF = new Build_formula_form();


    if (this->objectName().isEmpty())
        this->setObjectName(QString::fromUtf8("MainWindow"));
    this->resize(800, 600);
    centralwidget = new QWidget(this);
    centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
    add_atom_formula_button = new QPushButton(centralwidget);
    add_atom_formula_button->setObjectName(QString::fromUtf8("add_atom_formula_button"));
    add_atom_formula_button->setGeometry(QRect(0, 0, 471, 51));
    show_formula_button = new QPushButton(centralwidget);
    show_formula_button->setObjectName(QString::fromUtf8("show_formula_button"));
    show_formula_button->setGeometry(QRect(0, 50, 471, 51));
    and_button = new QPushButton(centralwidget);
    and_button->setObjectName(QString::fromUtf8("and_button"));
    and_button->setGeometry(QRect(0, 100, 471, 51));
    any_creation_button = new QPushButton(centralwidget);
    any_creation_button->setObjectName(QString::fromUtf8("any_creation_button"));
    any_creation_button->setGeometry(QRect(0, 250, 471, 51));
    or_button = new QPushButton(centralwidget);
    or_button->setObjectName(QString::fromUtf8("or_button"));
    or_button->setGeometry(QRect(0, 150, 471, 51));
    not_button = new QPushButton(centralwidget);
    not_button->setObjectName(QString::fromUtf8("not_button"));
    not_button->setGeometry(QRect(0, 200, 471, 51));
    swap_button = new QPushButton(centralwidget);
    swap_button->setObjectName(QString::fromUtf8("swap_button"));
    swap_button->setGeometry(QRect(0, 400, 471, 51));
    exist_button = new QPushButton(centralwidget);
    exist_button->setObjectName(QString::fromUtf8("exist_button"));
    exist_button->setGeometry(QRect(0, 300, 471, 51));
    build_formula_button = new QPushButton(centralwidget);
    build_formula_button->setObjectName(QString::fromUtf8("build_formula_button"));
    build_formula_button->setGeometry(QRect(0, 350, 471, 51));
    cancel_button = new QPushButton(centralwidget);
    cancel_button->setObjectName(QString::fromUtf8("cancel_button"));
    cancel_button->setGeometry(QRect(700, 20, 80, 26));
    save_button = new QPushButton(centralwidget);
    save_button->setObjectName(QString::fromUtf8("save_button"));
    save_button->setGeometry(QRect(700, 60, 80, 26));
    load_button = new QPushButton(centralwidget);
    load_button->setObjectName(QString::fromUtf8("load_button"));
    load_button->setGeometry(QRect(700, 100, 80, 26));
    guide_button = new QPushButton(centralwidget);
    guide_button->setObjectName(QString::fromUtf8("guide_button"));
    guide_button->setGeometry(QRect(700, 140, 80, 26));
    word_button = new QPushButton(centralwidget);
    word_button->setObjectName(QString::fromUtf8("word_button"));
    word_button->setGeometry(QRect(359, 500, 111, 26));
    sceme_button = new QPushButton(centralwidget);
    sceme_button->setObjectName(QString::fromUtf8("sceme_button"));
    sceme_button->setGeometry(QRect(360, 540, 111, 26));
    this->setCentralWidget(centralwidget);
    statusbar = new QStatusBar(this);
    statusbar->setObjectName(QString::fromUtf8("statusbar"));
    this->setStatusBar(statusbar);

    this->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
    add_atom_formula_button->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\260\321\202\320\276\320\274\320\260\321\200\320\275\321\203\321\216 \321\204\320\276\321\200\320\274\321\203\320\273\321\203", nullptr));
    show_formula_button->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\321\201\320\274\320\276\321\202\321\200\320\265\321\202\321\214 \320\262\321\201\320\265 \321\204\320\276\321\200\320\274\321\203\320\273\321\213", nullptr));
    and_button->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\321\201\321\202\321\200\320\276\320\265\320\275\320\270\320\265 \320\275\320\276\320\262\320\276\320\271 \321\204\320\276\321\200\320\274\321\203\320\273\321\213: &&", nullptr));
    any_creation_button->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\321\201\321\202\321\200\320\276\320\265\320\275\320\270\320\265 \320\275\320\276\320\262\320\276\320\271 \321\204\320\276\321\200\320\274\321\203\320\273\321\213: A", nullptr));
    or_button->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\321\201\321\202\321\200\320\276\320\265\320\275\320\270\320\265 \320\275\320\276\320\262\320\276\320\271 \321\204\320\276\321\200\320\274\321\203\320\273\321\213: V", nullptr));
    not_button->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\321\201\321\202\321\200\320\276\320\265\320\275\320\270\320\265 \320\275\320\276\320\262\320\276\320\271 \321\204\320\276\321\200\320\274\321\203\320\273\321\213: Not", nullptr));
    swap_button->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\274\320\265\320\275\320\260 \320\277\320\265\321\200\320\265\320\274\320\265\320\275\320\275\321\213\321\205", nullptr));
    exist_button->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\321\201\321\202\321\200\320\276\320\265\320\275\320\270\320\265 \320\275\320\276\320\262\320\276\320\271 \321\204\320\276\321\200\320\274\321\203\320\273\321\213 E", nullptr));
    build_formula_button->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\321\201\321\202\321\200\320\276\320\265\320\275\320\270\320\265 \320\274\320\275\320\276\320\266\320\265\321\201\321\202\320\262\320\260 \320\275\320\260 \320\276\321\201\320\275\320\276\320\262\320\265 \321\204\320\276\321\200\320\274\321\203\320\273\321\213", nullptr));
    cancel_button->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\274\320\265\320\275\320\260", nullptr));
    save_button->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
    load_button->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214", nullptr));
    guide_button->setText(QCoreApplication::translate("MainWindow", "\320\241\320\277\321\200\320\260\320\262\320\272\320\260", nullptr));
    word_button->setText(QCoreApplication::translate("MainWindow", "\320\255\320\272\321\201\320\277\320\276\321\200\321\202 \320\262 Word", nullptr));
    sceme_button->setText(QCoreApplication::translate("MainWindow", "\320\241\321\205\320\265\320\274\320\260", nullptr));


    QObject::connect(add_atom_formula_button, SIGNAL(clicked()), this, SLOT(add_atom()));
    QObject::connect(show_formula_button, SIGNAL(clicked()), this, SLOT(show_formula()));
    QObject::connect(and_button, SIGNAL(clicked()), this, SLOT(add_fun()));
    QObject::connect(or_button, SIGNAL(clicked()), this, SLOT(or_fun()));
    QObject::connect(not_button, SIGNAL(clicked()), this, SLOT(not_fun()));
    QObject::connect(any_creation_button, SIGNAL(clicked()), this, SLOT(any_creation_fun()));
    QObject::connect(exist_button, SIGNAL(clicked()), this, SLOT(exist_fun()));
    QObject::connect(swap_button, SIGNAL(clicked()), this, SLOT(swap_fun()));
    QObject::connect(build_formula_button, SIGNAL(clicked()), this, SLOT(build_formula_fun()));



    QMetaObject::connectSlotsByName(this);
}

void MainWindow::build_formula_fun(){
    ui_BF->show();
}

void MainWindow::swap_fun(){
    ui_SWF->show();
}


void MainWindow::exist_fun(){
    ui_EF->show();
}

void MainWindow::any_creation_fun(){
    ui_ACF->show();
}

void MainWindow::not_fun(){
    ui_NF->show();

}

void MainWindow::add_fun(){

    ui_AF->show();

}

void MainWindow::or_fun(){

    ui_OF->show();

}

void MainWindow::add_atom(){
    ui_AAF->show();

};



void MainWindow::show_formula(){
    ui_SF->show();
}


MainWindow::~MainWindow()
{
    delete ui;
}

