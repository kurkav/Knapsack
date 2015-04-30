TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    solvers/knapsackxeon.cpp \
    knapsacksolver.cpp \
    solvers/knapsackrecursive.cpp \
    solvers/knapsack.cpp \
    solvers/knapsackxeon.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    solvers/knapsackxeon.h \
    knapsacksolver.h \
    solvers/knapsackrecursive.h \
    solvers/knapsack.h \
    solvers/knapsackxeon.h

OTHER_FILES += \
    README.md

