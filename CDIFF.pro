# project.pro
QT += core gui widgets network
TEMPLATE = app

INCLUDEPATH += .
CONFIG += c++11
SOURCES += main.cpp
HEADERS += gguf.h

# Optional: Include debug symbols
#CONFIG += console
#CONFIG -= app_bundle


LIBS += -L/Users/macbook2015/Desktop/brew/lib -ltesseract -lleptonica

INCLUDEPATH += /Users/macbook2015/Desktop/brew/include /Users/macbook2015/Desktop/brew/lib
