TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG += qt

SOURCES += \
    Juliaset.cpp \
    png_stream_cgicc.cpp

HEADERS += \
    Juliaset.h \
    Mtrx.h \
    Mtrx.hpp

QMAKE_CXXFLAGS *= -fopenmp
LIBS += -fopenmp -lcgicc



