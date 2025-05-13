TEMPLATE = app
TARGET = GameDownloader
INCLUDEPATH += .

QT += core gui widgets network

SOURCES += \
    main.cpp \
    GameDownloader.cpp

HEADERS += \
    GameDownloader.h

FORMS += \
    GameDownloader.ui

RESOURCES += \
    GameDownloader.qrc
