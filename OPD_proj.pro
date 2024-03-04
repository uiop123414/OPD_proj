QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    add_atoms_formula_form.cpp \
    add_fun_form.cpp \
    any_creation_fun_form.cpp \
    build_formula_form.cpp \
    exist_fun_form.cpp \
    main.cpp \
    mainwindow.cpp \
    not_fun_form.cpp \
    or_fun_form.cpp \
    show_formula_form.cpp \
    swap_form.cpp

HEADERS += \
    add_atoms_formula_form.h \
    add_fun_form.h \
    any_creation_fun_form.h \
    build_formula_form.h \
    exist_fun_form.h \
    mainwindow.h \
    not_fun_form.h \
    or_fun_form.h \
    show_formula_form.h \
    swap_form.h

FORMS += \
    add_atoms_formula_form.ui \
    add_fun_form.ui \
    any_creation_fun_form.ui \
    build_formula_form.ui \
    exist_fun_form.ui \
    mainwindow.ui \
    not_fun_form.ui \
    or_fun_form.ui \
    show_formula_form.ui \
    swap_form.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
