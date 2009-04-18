TEMPLATE = app
TARGET = editor
DEPENDPATH += .
INCLUDEPATH += .
win32:debug {
    CONFIG += console
}

# Input
HEADERS += mainwindow.h notebox.h highlighter.h
SOURCES += mainwindow.cpp main.cpp notebox.cpp highlighter.cpp



