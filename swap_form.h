#ifndef SWAP_FORM_H
#define SWAP_FORM_H

#include <QWidget>

namespace Ui {
class Swap_form;
}

class Swap_form : public QWidget
{
    Q_OBJECT

public:
    explicit Swap_form(QWidget *parent = nullptr);
    ~Swap_form();

private:
    Ui::Swap_form *ui;
};

#endif // SWAP_FORM_H
