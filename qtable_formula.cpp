#include "qtable_formula.h"


#include <QModelIndex>
#include <QDebug>
#include <QPixmap>

QTable_Formula::QTable_Formula(QObject *parent)
    :QAbstractListModel(parent)
{
    values = new QList<furmalas_for_table>();
}

int QTable_Formula::rowCount(const QModelIndex &) const
{
    return values->count();
}

int QTable_Formula::columnCount(const QModelIndex &) const
{
    return 3;
}

QVariant QTable_Formula::data( const QModelIndex &index, int role ) const
{

    QVariant value;

        switch ( role )
        {
            case Qt::DisplayRole: //string
            {
                switch (index.column()) {
                    case 0: {
                        value = this->values->at(index.row()).getId();
                        break;
                    }
                    case 1: {
                        value = this->values->at(index.row()).getName();
                        break;
                    }
                    case 2: {
                        value = this->values->at(index.row()).getIcon();
                        break;
                    }
                }
            }
            break;

            case Qt::UserRole: //data
            {
                value = this->values->at(index.row()).getId();
            }
            break;

            default:
                break;
        }

    return value;
}

void QTable_Formula::populate(QList<furmalas_for_table> *newValues)
{
    int idx = this->values->count();
    this->beginInsertRows(QModelIndex(), 1, idx);
        this->values = newValues;
    endInsertRows();
 }

QVariant QTable_Formula::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return QString("ID");
        case 1:
            return QString("формула");
        case 2:
            return QString("ТИП");
        case 3:
            return QString("Свободные переменные");
        case 4:
            return QString("Описание");
        case 5:
            return QString("Addons");
        case 6:
            return QString("Обозначение");
        case 7:
            return QString("Нач Текст");
        }

    }
    return QVariant();
}
