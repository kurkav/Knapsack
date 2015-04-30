TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    knapsackxeon.cpp \
    knapsacksolver.cpp \
    knapsackrecursive.cpp \
    knapsack.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    knapsackxeon.h \
    knapsacksolver.h \
    knapsackrecursive.h \
    knapsack.h

