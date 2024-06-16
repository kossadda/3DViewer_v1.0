TEMPLATE = app
TARGET = 3d_viewer
CONFIG += c++17

SOURCES += \
    ./main.cpp \
    ./viewer.cpp \
    ./glwidget.cpp \
    ./../modules/parse.c \
    ./../modules/matrix.c \
    ./../modules/afine.c

HEADERS += \
    ./viewer.h \
    ./glwidget.h \
    ./gif.h \
    ./../modules/include/parse.h \
    ./../modules/include/matrix.h \
    ./../modules/include/afine.h \
    ./../modules/include/common.h \
    ./../modules/include/objects.h

FORMS += \
    ./viewer.ui

RESOURCES += \
    ./../resources/resource.qrc

QT += widgets opengl

INCLUDEPATH += \
    ./ \
    ./../modules/include

QMAKE_CXXFLAGS += -std=c++17

LIBS += -L$$PWD -l:./../3d_viewer.a

# Указываем цели установки
target.path = $$[QT_INSTALL_BINS]
INSTALLS += target
