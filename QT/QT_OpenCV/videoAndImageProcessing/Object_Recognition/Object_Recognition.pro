#-------------------------------------------------
#
# Project created by QtCreator 2019-07-11T17:46:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Object_Recognition
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
        opencvwidget.cpp

HEADERS  += mainwindow.h \
            opencvwidget.h

FORMS    += mainwindow.ui


INCLUDEPATH += D:\opencv\release\install\include

#Note: must build libraries using cmake for mingw compiler
LIBS += D:\opencv\release\install\x64\mingw\bin\libopencv_calib3d249.dll
LIBS += D:\opencv\release\install\x64\mingw\bin\libopencv_contrib249.dll
LIBS += D:\opencv\release\install\x64\mingw\bin\libopencv_core249.dll
LIBS += D:\opencv\release\install\x64\mingw\bin\libopencv_highgui249.dll
LIBS += D:\opencv\release\install\x64\mingw\bin\libopencv_imgproc249.dll
LIBS += D:\opencv\release\install\x64\mingw\bin\libopencv_features2d249.dll

