QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    data.cpp \
    daydialog.cpp \
    dayinmonthwidget.cpp \
    eventcreator.cpp \
    eventnote.cpp \
    eventwidget.cpp \
    main.cpp \
    eventcalendar.cpp \
    monthviewer.cpp \
    sqlhandler.cpp \
    typebox.cpp \
    wholeviewer.cpp

HEADERS += \
    data.h \
    daydialog.h \
    dayinmonthwidget.h \
    event.h \
    eventcalendar.h \
    eventcreator.h \
    eventnote.h \
    eventwidget.h \
    monthviewer.h \
    sqlhandler.h \
    typebox.h \
    wholeviewer.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
  res.qrc
