#ifndef MAINWINDOW_RED_H
#define MAINWINDOW_RED_H

#include <QMainWindow>
#include <add_atoms_formula_form.h>
#include <add_fun_form.h>
#include <or_fun_form.h>
#include <not_fun_form.h>
#include <vector>
#include <formula.h>
#include <QTableWidgetItem>

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
    Or_fun_form *ui_NKF;
    Or_fun_form *ui_NDF;
    Or_fun_form *ui_NNF;
    vector <EntityBase *> all_entities;
    QTableWidgetItem* convertWideToUtf8(const wchar_t* wideString);

    void updateTable();

public slots:
    void add_atom();
    void add_kon();
    void add_diz();
    void add_not();
    void recieveData(EntityVariable ev1, EntityVariable ev2);
    void update_values(Formula * formula);
};

#endif // MAINWINDOW_RED_H
