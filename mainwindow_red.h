#ifndef MAINWINDOW_RED_H
#define MAINWINDOW_RED_H

#include <QMainWindow>
#include <add_atoms_formula_form.h>

namespace Ui {
class mainwindow_red;
}

class mainwindow_red : public QMainWindow
{
    Q_OBJECT

public:
    explicit mainwindow_red(QWidget *parent = nullptr);
    ~mainwindow_red();

private:
    Ui::mainwindow_red *ui;
    Add_atoms_formula_form *ui_AAF;

public slots:
    void add_atom();
};

#endif // MAINWINDOW_RED_H
