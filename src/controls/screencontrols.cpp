#include "screencontrols.h"

ScreenControls::ScreenControls(QObject *parent) : QObject(parent)
{

}
void ScreenControls::changeScreen(Screen screen) {
    if(screen == _activeScreen)
        return;
    _activeScreen = screen;
    emit screenChanged();
}

