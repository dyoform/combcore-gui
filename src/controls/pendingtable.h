#ifndef PENDINGTABLE_H
#define PENDINGTABLE_H

#include <qqml.h>
#include <QAbstractTableModel>
#include "datamodel.h"

class PendingTable : public QAbstractTableModel
{
    Q_OBJECT
    Q_PROPERTY(int selectedRow READ selectedRow WRITE selectRow NOTIFY selectedRowChanged)
    QML_ELEMENT

public:
    void inject(DataModel* model) {
        _model = model;
        connect(_model, SIGNAL(dataChanged()), this, SLOT(updateData()));
        rows =_model->pending_commits.size();
        updateData();
    }
    int rowCount(const QModelIndex & = QModelIndex()) const override
    {
        return rows;
    }

    int columnCount(const QModelIndex & = QModelIndex()) const override
    {
        return 2;
    }

    QVariant data(const QModelIndex &index, int role) const override
    {
        Commit* c = _model->pending_commits[index.row()].get();
        switch (role) {
            case Qt::DisplayRole:
                return index.column() == 0 ? c->ID(): c->typeName();
            default:
                break;
        }

        return QVariant();
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override {
        return section == 0 ? QString("Address") : QString("Type");
    }

    QHash<int, QByteArray> roleNames() const override
    {
        return { {Qt::DisplayRole, "display"} };
    }

    int selectedRow() {return _selectedRow;}
private:
    DataModel* _model;
    int _selectedRow;
    int rows = 0;
public slots:
    void selectRow(int row);
    void updateData() {
        int old = rows;
        rows = _model->pending_commits.size();
        beginResetModel();
        emit dataChanged(createIndex(0,0), createIndex(old, 2));
        endResetModel();
    }
signals:
    void selectedRowChanged();
};

#endif // PENDINGTABLE_H
