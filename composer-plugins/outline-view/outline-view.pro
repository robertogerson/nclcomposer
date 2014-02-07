include (../plugins-common.pri)
TARGET          = outline_view
QT              += xml

macx:LIBS +=    -L$$quote(/Library/Application Support/Composer/Extensions) \
                -lNCLLanguageProfile

win32:LIBS +=   -lNCLLanguageProfile

INCLUDEPATH     +=  src \
                    ../ncl-text-editor/include \

HEADERS         =   src/NCLTreeWidget.h \
                    src/NCLParser.h \
                    src/OutlineViewPlugin.h \
                    src/OutlineViewFactory.h

SOURCES         =   src/NCLTreeWidget.cpp \
                    src/NCLParser.cpp \
                    src/OutlineViewPlugin.cpp \
                    src/OutlineViewFactory.cpp

INSTALLS        =   target

RESOURCES += \
    ../common-resources/images.qrc \
    ../common-resources/language.qrc

OTHER_FILES += \
    outline_view.json
