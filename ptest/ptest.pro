TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        CPU.cpp \
        Common.cpp \
        Computer.cpp \
        MatrixRandom.cpp \
        PerformanceTest.cpp \
        PreciseTimer.cpp \
        SquareMatrix.cpp \
        Tests.cpp \
        main.cpp \
        utils.cpp

HEADERS += \
    CPU.h \
    Common.h \
    Computer.h \
    MatrixRandom.h \
    PerformanceTest.h \
    PreciseTimer.h \
    SquareMatrix.h \
    Tests.h \
    utils.h

unix:LIBS += -pthread
