#ifndef OR_FUN_FORM_H
#define OR_FUN_FORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QWidget>
#include <vector>
#include <formula.h>
namespace Ui {
class Or_fun_form;
}

class Or_fun_form : public QWidget
{
    Q_OBJECT

public:
    explicit Or_fun_form(QWidget *parent = nullptr);
    ~Or_fun_form();
    void change_type(int new_type,vector <EntityBase *>  _all_entities);

private:

    QLabel *name_label;
    QListView *left_listView;
    QPushButton *force_right_Button;
    QPushButton *right_Button;
    QPushButton *left_Button;
    QPushButton *force_left_Button;
    QListView *upper_listView;
    QRadioButton *to_all_formulas_radioButton;
    QRadioButton *bin_radioButton;
    QListView *low_listView;
    QRadioButton *perform_to_all_list_radioButton;
    QPushButton *perform_Button;
    QPushButton *cancel_Button;
    vector <EntityBase *>  all_entities;

    int type = 0;


    Ui::Or_fun_form *ui;

public slots:
    void new_accept();
};

#endif // OR_FUN_FORM_H
