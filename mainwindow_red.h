#ifndef MAINWINDOW_RED_H
#define MAINWINDOW_RED_H

#include <QMainWindow>

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
};

#endif // MAINWINDOW_RED_H
