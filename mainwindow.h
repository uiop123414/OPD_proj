#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>


#include <add_atoms_formula_form.h>
#include <show_formula_form.h>
#include <add_fun_form.h>
#include <or_fun_form.h>
#include <not_fun_form.h>
#include <any_creation_fun_form.h>
#include <exist_fun_form.h>
#include <build_formula_form.h>
#include <swap_form.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QWidget *centralwidget;
    QPushButton *add_atom_formula_button;
    QPushButton *show_formula_button;
    QPushButton *and_button;
    QPushButton *any_creation_button;
    QPushButton *or_button;
    QPushButton *not_button;
    QPushButton *swap_button;
    QPushButton *exist_button;
    QPushButton *build_formula_button;
    QPushButton *cancel_button;
    QPushButton *save_button;
    QPushButton *load_button;
    QPushButton *guide_button;
    QPushButton *word_button;
    QPushButton *sceme_button;
    QStatusBar *statusbar;
    Ui::MainWindow *ui;

private:

    Add_atoms_formula_form *ui_AAF;
    Show_formula_form *ui_SF;
    Add_fun_form *ui_AF;
    Or_fun_form *ui_OF;
    Not_fun_form * ui_NF;
    Any_creation_fun_form *ui_ACF;
    Exist_fun_form *ui_EF;
    Build_formula_form *ui_BF;
    Swap_form * ui_SWF;

public slots:
    void add_atom();
    void show_formula();
    void add_fun();
    void or_fun();
    void not_fun();
    void any_creation_fun();
    void exist_fun();
    void swap_fun();
    void build_formula_fun();
};
#endif // MAINWINDOW_H
