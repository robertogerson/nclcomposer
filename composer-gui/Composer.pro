TARGET = composer
TEMPLATE = app
CONFIG += qt warn_on debug console

#CONFIG += clubencl
CONFIG += runssh_on
QT += xml network webkit

DEFINES += NCLCOMPOSER_GUI_VERSION=\"\\\"0.1.0\\\"\"

# DEFINES += USE_MDI

RC_FILE = images/nclcomposer.rc

MOC_DIR     =   .moc
OBJECTS_DIR =   .obj
UI_DIR      =   .ui

macx {
  TARGET = Composer
  INSTALLBASE = /Applications
  ICON =  images/Composer.icns
}
else:unix {
  isEmpty(PREFIX) {
    PREFIX = /usr/local
  } 
  INSTALLBASE = $$PREFIX
  
  DATADIR = $$PREFIX/share

  # set the path to install desktop configuration
  desktop.path = $$DATADIR/applications/
  desktop.files = $${TARGET}.desktop

  icon64.path = $$DATADIR/icons/gnome/64x64/apps
  icon64.files = images/$${TARGET}.svg

  icon48.path = $$DATADIR/icons/gnome/48x48/apps
  icon48.files = images/$${TARGET}.svg
}
else:win32 {
  INSTALLBASE = "C:/Composer"
}

DEFINES += EXT_DEFAULT_PATH=\"\\\"$$PREFIX\\\"\"

unix:!macx {
    target.path = $$INSTALLBASE/bin

    QMAKE_LFLAGS += -Wl,--rpath=\'\$\$ORIGIN/../lib/composer\'
    QMAKE_LFLAGS += --rpath=\'\$\$ORIGIN/../lib/composer/extensions\'
}
else {
    target.path = $$INSTALLBASE
}

INCLUDEPATH +=  include

INCLUDEPATH   +=  ../composer-core/core/include
LIBS          +=  -L../composer-core/core

macx {
    LIBS += -framework ComposerCore
    INCLUDEPATH += /Library/Frameworks/ComposerCore.framework/
}
else:unix {
    LIBS += -L$$INSTALLBASE/lib/composer -lComposerCore
    INCLUDEPATH +=  $$INSTALLBASE/include/composer \
                    $$INSTALLBASE/include/composer/core
}
else:win32 {
    LIBS += -L$$INSTALLBASE -lComposerCore1
    INCLUDEPATH += $$INSTALLBASE/include/composer \
                   $$INSTALLBASE/include/composer/core
}

clubencl {
    DEFINES += WITH_CLUBENCL
    #if clube ncl
    LIBS += -lquazip
}

runssh_on {
  LIBS += -lssh2
}

SOURCES += main.cpp \
    src/ComposerMainWindow.cpp \
    src/PreferencesDialog.cpp \
    src/PerspectiveManager.cpp \
    src/PluginDetailsDialog.cpp \
    src/EnvironmentPreferencesWidget.cpp \
    src/WelcomeWidget.cpp \
    src/AboutDialog.cpp \
    src/SimpleSSHClient.cpp \
    src/RunGingaConfig.cpp

HEADERS += include/ComposerMainWindow.h \
    include/PreferencesDialog.h \
    include/PerspectiveManager.h \
    include/PluginDetailsDialog.h \
    include/EnvironmentPreferencesWidget.h \
    include/IPreferencePage.h \
    include/WelcomeWidget.h \
    include/AboutDialog.h \
    include/SimpleSSHClient.h \
    include/RunGingaConfig.h

RESOURCES += images.qrc

FORMS   += ui/PreferencesDialog.ui \
    ui/ComposerMainWindow.ui \
    ui/PerspectiveManager.ui \
    ui/RunGingaConfig.ui \
    ui/PluginDetailsDialog.ui \
    ui/EnvironmentPreferencesWidget.ui \
    ui/WelcomeWidget.ui \
    ui/AboutDialog.ui

unix:!macx {
    INSTALLS += target desktop icon64 icon48
} else {
    INSTALLS += target
}

OTHER_FILES += LICENSE.LGPL
