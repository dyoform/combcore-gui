#include "pendingtable.h"

void PendingTable::selectRow(int row) {
    if(row == _selectedRow || row < -1 || row >= _model->pending_commits.size())
        return;
    _selectedRow = row;
    emit selectedRowChanged();
}

