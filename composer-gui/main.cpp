#include <QtGui/QApplication>
#include <QResource>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(true);
    a.setStyleSheet("QTabWidget::tab-bar { alignment: center; } \
                     QTabWidget::pane { position: absolute; top: -0.5em; }");
    QResource::registerResource("images.qrc");
    QCoreApplication::setOrganizationName("Telemidia Lab");
    QCoreApplication::setOrganizationDomain("telemidia.pucrio.br");
    QCoreApplication::setApplicationName("composer");
    QPixmap mPix(":/mainwindow/icon");
    QSplashScreen splash(mPix);
    splash.blockSignals(true);
    splash.show();
    MainWindow w;
    w.setStyleSheet("font-size: 12px");
    splash.finish(&w);
    w.show();
    return a.exec();
}
