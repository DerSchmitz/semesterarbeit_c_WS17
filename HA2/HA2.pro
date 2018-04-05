TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    txttokenlib.cpp \
    xmltokenlib.cpp

HEADERS += \
    cltxttoken.h \
    clxmltoken.h
