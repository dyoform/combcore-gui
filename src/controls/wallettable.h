#ifndef WALLETTABLE_H
#define WALLETTABLE_H

#include <qqml.h>
#include <QAbstractTableModel>
#include <QtGlobal>
#include "datamodel.h"

class WalletTable : public QAbstractTableModel
{
    Q_OBJECT
    Q_PROPERTY(int selectedRow READ selectedRow WRITE selectRow NOTIFY selectedRowChanged)
    Q_PROPERTY(int selectedType READ selectedType NOTIFY selectedTypeChanged)
    Q_PROPERTY(Construct* selectedConstruct READ selectedConstruct NOTIFY selectedConstructChanged)
    QML_ELEMENT

public:
    void inject(DataModel* model) {
        _model = model;
        connect(_model, SIGNAL(dataChanged()), this, SLOT(updateData()));
        connect(_model, SIGNAL(connectedChanged(bool)), this, SLOT(connectedChanged(bool)));
        rows =_model->constructs.size();
        updateData();
    }
    int rowCount(const QModelIndex & = QModelIndex()) const override
    {
        return rows;
    }

    int columnCount(const QModelIndex & = QModelIndex()) const override
    {
        return 3;
    }

    QVariant data(const QModelIndex &index, int role) const override
    {
        Construct* c = _model->constructs[index.row()].get();
        if(role != Qt::DisplayRole) {
            return QVariant();
        }
        switch (index.column()) {
        case 0:
            return c->typeName();
        case 1:
            return c->Active();
        case 2:
            return c->ID();
        }

        return QVariant();
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override {
        switch(section) {
        case 0:
            return QString("Type");
        case 1:
            return QString("Active");
        case 2:
            return QString("Address");
        }

        return QVariant();
    }

    QHash<int, QByteArray> roleNames() const override
    {
        return { {Qt::DisplayRole, "display"} };
    }

    int selectedRow() {return _selectedRow;}
    ConstructType selectedType() {return _selectedType;}
    Construct* selectedConstruct() {return _selectedConstruct;}
private:
    DataModel* _model;
    int rows = 0;
    int _selectedRow=-1;
    ConstructType _selectedType = TYPE_NONE;
    Construct* _selectedConstruct;
public slots:
    void selectRow(int row);
    void updateData() {
        int old = rows;
        rows = _model->constructs.size();
        beginResetModel();
        //emit dataChanged(createIndex(0,0), createIndex(rows, 3));
        endResetModel();

        selectRow(qMin(_selectedRow, rows));
    }
    void connectedChanged(bool connected) {
        if(!connected) {
            _selectedConstruct = nullptr;
            _selectedRow=-1;
            _selectedType = TYPE_NONE;

            emit selectedConstructChanged();
            emit selectedRowChanged();
            emit selectedTypeChanged();
        };
    }
signals:
    void selectedRowChanged();
    void selectedTypeChanged();
    void selectedConstructChanged();
};
#endif // WALLETTABLE_H
