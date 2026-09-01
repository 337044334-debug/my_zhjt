QT       += core gui network mqtt sql

#serialport暂时注释掉

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    login.cpp \
    main.cpp \
    my_lineedit.cpp \
    syszuxpinyin.cpp \
    widget.cpp \
    my_wifi.cpp \
    set_wifi.cpp \
    settings.cpp \
    weather.cpp \
    collentdatathread.cpp \
    my_humiture.cpp \
    control.cpp \
    pe15thread.cpp \
    register.cpp

HEADERS += \
    login.h \
    my_lineedit.h \
    syszuxpinyin.h \
    widget.h \
    my_wifi.h \
    set_wifi.h \
    settings.h \
    weather.h \
    collentdatathread.h \
    my_humiture.h \
    control.h \
    pe15thread.h \
    register.h


FORMS += \
    login.ui \
    syszuxpinyin.ui \
    widget.ui \
    my_wifi.ui \
    set_wifi.ui \
    settings.ui \
    weather.ui \
    my_humiture.ui \
    control.ui \
    register.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icon.qrc \
    qtr.qrc
