#include "wallettable.h"

void WalletTable::selectRow(int row) {
    if(row < -1 || row >= _model->constructs.size())
        return;
    _selectedRow = row;


    _selectedConstruct = _model->constructs[_selectedRow].get();

    _selectedType = _selectedConstruct->type();
    emit selectedRowChanged();
    emit selectedTypeChanged();
    emit selectedConstructChanged();
}

