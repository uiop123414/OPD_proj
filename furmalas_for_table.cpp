#include "furmalas_for_table.h"




furmalas_for_table::furmalas_for_table()
{

}

furmalas_for_table::furmalas_for_table(int id, QString name, QString icon)
{
    this->id = id;
    this->name = name;//формула
    this->icon = icon; // ТИП
    this->free_var="";// Свободные переменные
    this->desc="";   // Описание
    this->addons="";  // Addons
    this->Designation="";// Обозначение
    this->st_text="";    // Нач Текст
}

QString furmalas_for_table::getIcon() const
{
    return icon;
}

void furmalas_for_table::setIcon(const QString &value)
{
    icon = value;
}

QString furmalas_for_table::getName() const
{
    return name;
}

void furmalas_for_table::setName(const QString &value)
{
    name = value;
}

int furmalas_for_table::getId() const
{
    return id;
}

void furmalas_for_table::setId(int value)
{
    id = value;
}
