#ifndef ADD_FUN_FORM_H
#define ADD_FUN_FORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QWidget>


namespace Ui {
class Add_fun_form;
}

class Add_fun_form : public QWidget
{
    Q_OBJECT

public:
    explicit Add_fun_form(QWidget *parent = nullptr);
    ~Add_fun_form();

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

    Ui::Add_fun_form *ui;
};

#endif // ADD_FUN_FORM_H
