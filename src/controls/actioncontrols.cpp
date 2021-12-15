#include "actioncontrols.h"

ActionControls::ActionControls(QObject *parent) : QObject(parent)
{

}
void ActionControls::changeAction(Action action) {
    if(action == _activeAction)
        return;
    _activeAction = action;
    emit actionChanged();
}

