#ifndef SCREENCONTROLS_H
#define SCREENCONTROLS_H

#include <QObject>
#include <qqml.h>

class ScreenControls : public QObject {
    Q_OBJECT
    Q_PROPERTY(Screen activeScreen READ activeScreen WRITE changeScreen NOTIFY screenChanged)
    Q_ENUMS(Screen)
    QML_ELEMENT
public:
    enum Screen {
        SCREEN_OVERVIEW,
        SCREEN_WALLET,
        SCREEN_ACTIONS,
        SCREEN_SETTINGS,
        SCREEN_NONE
    };
    explicit ScreenControls(QObject *parent = nullptr);
    Screen activeScreen() {return _activeScreen; };
private:
    Screen _activeScreen = SCREEN_OVERVIEW;
public slots:
    void changeScreen(Screen screen);
signals:
    void screenChanged();
};

#endif // SCREENCONTROLS_H
