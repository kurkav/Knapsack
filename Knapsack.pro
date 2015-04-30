TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS+= -fopenmp
QMAKE_LFLAGS +=  -fopenmp

SOURCES += main.cpp \
    solvers/knapsackxeon.cpp \
    knapsacksolver.cpp \
    solvers/knapsackrecursive.cpp \
    solvers/knapsack.cpp \

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    solvers/knapsackxeon.h \
    knapsacksolver.h \
    solvers/knapsackrecursive.h \
    solvers/knapsack.h \

OTHER_FILES += \
    README.md

