#-------------------------------------------------
#
# Project created by QtCreator 2018-03-22T10:28:29
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = seg_codorna
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp

INCLUDEPATH += "C:\OpenCV-QT\install\include"
LIBS += -L"C:\OpenCV-QT\install\x86\mingw\bin" \
    libopencv_core320 \
    libopencv_highgui320 \
    libopencv_videoio320 \
    libopencv_imgcodecs320 \
    libopencv_imgproc320 \
    libopencv_features2d320 \
    libopencv_calib3d320
