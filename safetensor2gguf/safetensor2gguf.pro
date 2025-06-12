# project.pro
QT += core gui widgets
TEMPLATE = app

INCLUDEPATH += .
CONFIG += c++11
SOURCES += main.cpp \
    safetensors.cc

# Optional: Include debug symbols
#CONFIG += console
#CONFIG -= app_bundle

HEADERS += \
    ggml.h \
    gguf.h \
    safetensors.hh

LIBS += -L/Users/macbook2015/Desktop/brew/lib -lllama

INCLUDEPATH += /Users/macbook2015/Desktop/brew/include /Users/macbook2015/Desktop/brew/lib
