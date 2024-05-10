#ifndef FURMALAS_FOR_TABLE_H
#define FURMALAS_FOR_TABLE_H

#include <QString>
#include <vector>


class furmalas_for_table
{
public:
    furmalas_for_table();
    furmalas_for_table(int id, QString name, QString icon);
    QString getIcon() const;
    void setIcon(const QString &value);

    QString getName() const;
    void setName(const QString &value);

    int getId() const;
    void setId(int value);

private:
    int id;
    QString icon;
    QString name;
    QString desc;
    QString free_var;
    QString Designation;
    QString addons;
    QString st_text;
};

#endif // FURMALAS_FOR_TABLE_H
