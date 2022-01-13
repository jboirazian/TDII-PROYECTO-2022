QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    agregar.cpp \
    main.cpp \
    mainwindow.cpp \
    personal.cpp \
    dialog.cpp

HEADERS += \
    agregar.h \
    main.h \
    mainwindow.h \
    personal.h \
    globales.h \
    libusb.h \
    dialog.h

FORMS += \
    agregar.ui \
    mainwindow.ui \
    dialog.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/LIBUSB_Binary/MinGW32/dll/ -llibusb-1.0.dll
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/LIBUSB_Binary/MinGW32/dll/ -llibusb-1.0.dll

INCLUDEPATH += $$PWD/LIBUSB_Binary/MinGW32/dll
DEPENDPATH += $$PWD/LIBUSB_Binary/MinGW32/dll

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
