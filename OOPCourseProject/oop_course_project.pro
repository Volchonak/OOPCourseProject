QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AddNewAbonement.cpp \
    OperatingWindow.cpp \
    Person.cpp \
    SwimmingPoolSeasonTicket.cpp \
    main.cpp \
    mainwindow.cpp \
    Exception.cpp

HEADERS += \
    AddNewAbonement.h \
    OperatingWindow.h \
    Person.h \
    SwimmingPoolSeasonTicket.h \
    mainwindow.h \
    Exception.h

FORMS += \
    AddNewAbonement.ui \
    mainwindow.ui \
    operatingwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
