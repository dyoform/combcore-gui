QT += qml quick svg
QTPLUGIN += qsvg qsvgicon

CONFIG += c++11 qmltypes
QML_IMPORT_NAME = combcore
QML_IMPORT_MAJOR_VERSION = 1

SOURCES += \
        src/constructs/commit.cpp \
        src/constructs/construct.cpp \
        src/constructs/key.cpp \
        src/constructs/stack.cpp \
        src/constructs/transaction.cpp \
        src/datamodel.cpp \
        src/controls/actioncontrols.cpp \
        src/guimodel.cpp \
        src/main.cpp \
        src/controls/pendingtable.cpp \
        src/controls/wallettable.cpp

RESOURCES += qml/qml.qrc

INCLUDEPATH += src src/controls src/constructs

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
    src/constructs/key.h \
    src/constructs/stack.h \
    src/constructs/transaction.h \
    src/datamodel.h \
    src/controls/actioncontrols.h \
    src/guimodel.h \
    src/controls/pendingtable.h \
    src/controls/wallettable.h
