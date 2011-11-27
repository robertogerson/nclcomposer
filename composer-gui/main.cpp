/* Copyright (c) 2011 Telemidia/PUC-Rio.
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *
 * Contributors:
 *    Telemidia/PUC-Rio - initial API and implementation
 */
#include <QtGui/QApplication>
#include <QResource>
#include <QObject>
#include "ComposerMainWindow.h"

using namespace composer::gui;

/*!
 \mainpage
This is the online reference for developing with the NCL Composer.
NCL Composer is a multiplatform and flexible multimedia authoring tool. It was
first developed for NCL (Nested Context Language) support, but its flexible
architecture allows to extend it to support almost all other multimedia
languages, e.g. SMIL, SVG, and HTML 5.

\section sec_features Features
List of features

\section sec_tutorials Tutorials
List of tutorials

\section sec_copyright Copyright Policy
NCL Composer is developed by Telemidia/PUC-Rio since 2011 and available over
Eclipse Public License.
*/
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(true);

    QResource::registerResource("images.qrc");
    QCoreApplication::setOrganizationName("Telemidia Lab");
    QCoreApplication::setOrganizationDomain("telemidia.pucrio.br");
    QCoreApplication::setApplicationName("composer");
    QPixmap mPix(":/mainwindow/nclomposer-full");
    QSplashScreen splash(mPix);

    splash.blockSignals(true);
    splash.show();

    //make the library search path include the application dir on windows
    //this is so the plugins can find the dlls they are linked to at run time
    QApplication::addLibraryPath(QApplication::applicationDirPath());

    ComposerMainWindow w(a);
    splash.finish(&w);

    w.show();

    return a.exec();
}
