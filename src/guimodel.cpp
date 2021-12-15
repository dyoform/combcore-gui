#include "guimodel.h"

GUIModel::GUIModel(DataModel* model)
{
    _model = model;
    _pendingTable.inject(model);
    _walletTable.inject(model);
}
