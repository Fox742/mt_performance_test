TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        CPU.cpp \
        Common.cpp \
        Computer.cpp \
        MatrixRandom.cpp \
        SquareMatrix.cpp \
        main.cpp

HEADERS += \
    CPU.h \
    Common.h \
    Computer.h \
    MatrixRandom.h \
    SquareMatrix.h
