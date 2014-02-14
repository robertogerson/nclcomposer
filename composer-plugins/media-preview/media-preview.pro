######################################################################
# Automatically generated by qmake (2.01a) Sat Jan 28 14:31:14 2012
######################################################################
include(../plugins-common.pri)

QT += phonon
QT += gui
QT += xml
CONFIG +=qtestlib


#TEMPLATE = app
TARGET = mediapreview
DEPENDPATH += .
INCLUDEPATH += . src

release {
LIBS      +=    -L../ncl-textual-view/deps/QScintilla-gpl-2.8/Qt4Qt5/release \
                -lqscintilla2_telem
}else:debug {
LIBS      +=    -L../ncl-textual-view/deps/QScintilla-gpl-2.8/Qt4Qt5/debug \
                -lqscintilla2_telem
}

CODECFORTR = UTF-8

# Input
SOURCES += \
    src/mediapreviewfactory.cpp \
    src/audioplayer.cpp \
    src/imagview.cpp \
    src/gifview.cpp \
    src/textview.cpp \
    src/hypertextview.cpp \
    src/nclview.cpp \
    src/luaview.cpp \
    src/mediapreviewplugin.cpp \
    src/videoplayer.cpp

HEADERS += \
    src/mediapreviewfactory.h \
    src/mediapreviewplugin.h \
    src/audioplayer.h \
    src/imagview.h \
    src/gifview.h \
    src/textview.h \
    src/hypertextview.h \
    src/nclview.h \
    src/luaview.h \
    src/videoplayer.h

FORMS += \
    ui/videoplayer.ui

RESOURCES += \
    media-preview.qrc

OTHER_FILES += \
    media_preview_plugin.json
