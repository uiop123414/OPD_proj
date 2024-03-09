#ifndef QTABLE_FORMULA_H
#define QTABLE_FORMULA_H

#include <QAbstractListModel>
#include "furmalas_for_table.h"
#include <QModelIndex>

class QTable_Formula : public QAbstractListModel
{
    Q_OBJECT

public:    QTable_Formula(QObject *parent=nullptr);
    int rowCount(const QModelIndex &) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    void populate(QList<furmalas_for_table> *newValues);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
private:
    QList<furmalas_for_table> *values;
private:
};

#endif // QTABLE_FORMULA_H
