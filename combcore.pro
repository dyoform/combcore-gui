QT += qml quick svg network
RC_ICONS = combcore.ico
TARGET = combcore-qt

CONFIG += c++11 qmltypes
CONFIG += static
QML_IMPORT_NAME = combcore
QML_IMPORT_MAJOR_VERSION = 1

SOURCES += \
        src/constructs/commit.cpp \
        src/constructs/construct.cpp \
        src/constructs/key.cpp \
        src/constructs/stack.cpp \
        src/constructs/transaction.cpp \
        src/controls/actions/commandaction.cpp \
        src/controls/actions/createstackaction.cpp \
        src/controls/actions/createtransactionaction.cpp \
        src/controls/actions/generatekeyaction.cpp \
        src/controls/actionscreen.cpp \
        src/controls/overviewscreen.cpp \
        src/controls/screencontrols.cpp \
        src/controls/settingsscreen.cpp \
        src/controls/walletscreen.cpp \
        src/datamodel.cpp \
        src/guimodel.cpp \
        src/main.cpp \
        src/controls/pendingtable.cpp \
        src/controls/wallettable.cpp

RESOURCES += qml/qml.qrc

INCLUDEPATH += src src/controls src/constructs src/controls/actions

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = qml

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH = qml

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    src/constructs/commit.h \
    src/constructs/construct.h \
    src/constructs/decider.h \
    src/constructs/key.h \
    src/constructs/merklesegment.h \
    src/constructs/stack.h \
    src/constructs/transaction.h \
    src/controls/actions/commandaction.h \
    src/controls/actions/commitaddressaction.h \
    src/controls/actions/createmerklesegmentaction.h \
    src/controls/actions/createstackaction.h \
    src/controls/actions/createtransactionaction.h \
    src/controls/actions/decidemerklesegmentaction.h \
    src/controls/actions/generatedecideraction.h \
    src/controls/actions/generatekeyaction.h \
    src/controls/actions/signdecideraction.h \
    src/controls/actionscreen.h \
    src/controls/overviewscreen.h \
    src/controls/screencontrols.h \
    src/controls/settingsscreen.h \
    src/controls/walletscreen.h \
    src/datamodel.h \
    src/guimodel.h \
    src/controls/pendingtable.h \
    src/controls/wallettable.h

DISTFILES +=
