/****************************************************************************
**
** Copyright (C) 2004-2006 Trolltech ASA. All rights reserved.
**
** This file is part of the example classes of the Qt Toolkit.
**
** Licensees holding a valid Qt License Agreement may use this file in
** accordance with the rights, responsibilities and obligations
** contained therein.  Please consult your licensing agreement or
** contact sales@trolltech.com if any conditions of this licensing
** agreement are not clear to you.
**
** Further information about Qt licensing is available at:
** http://www.trolltech.com/products/qt/licensing.html or by
** contacting info@trolltech.com.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#include <QApplication>
#include <QTreeView>

#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Q_INIT_RESOURCE(ncl_textual_plugin);

    MainWindow mainWin;
    mainWin.show();

/*    app.setStyleSheet("QDockWidget {\
                            border: 1px solid lightgray;\
                        }\
                        QDockWidget::title {\
                            text-color: #FFFFFF; \
                            background: #000000;\
                            padding-left: 5px;\
                            padding-top: 5px;\
                        }");
*/
    return app.exec();
}
