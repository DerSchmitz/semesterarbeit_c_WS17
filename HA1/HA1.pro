TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    xmltokenlib.cpp \
    txttokenlib.cpp

DISTFILES += \
    ../build-HA1-Desktop_Qt_5_2_1_MinGW_32bit-Debug/listProducts.xml \
    ../build-HA1-Desktop_Qt_5_2_1_MinGW_32bit-Debug/allowed-tags.dtd \
    ../build-HA1-Desktop_Qt_5_2_1_MinGW_32bit-Debug/products.txt

HEADERS += \
    cltxttoken.h \
    clxmltoken.h
