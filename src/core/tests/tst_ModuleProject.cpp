/* Copyright (C) 2011-2018 PUC-Rio/TeleMídia Lab.

 NCL Composer is free software: you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published
 by the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 NCL Composer is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Lesser General Public License for more details.

 You should have received a copy of the GNU General Lesser Public License
 along with NCL Composer.  If not, see <http://www.gnu.org/licenses/>. */

#include "tst_ModuleProject.h"

#include "tst_Utils.h"

#include <fstream>
#include <iostream>
using namespace std;

void
tst_ModuleProject::initTestCase ()
{
  pjControl = ProjectControl::getInstance ();
  resourceDir = "resources";
  resourceDir
      = resourceDir + QDir::separator () + "documents" + QDir::separator ();

  QString baseDir = "..";
  profileDir
      = baseDir + QDir::separator () + "extensions" + QDir::separator ();
  // +"composer"+QDir::separator();
  lgControl = LanguageControl::getInstance ();

  pluginList = TestUtil::getPluginList ();

  pgControl = PluginControl::getInstance ();

  connect (pgControl, SIGNAL (addPluginWidgetToWindow (
                          IPluginFactory *, IPlugin *, Project *, int)),
           &showWidgets, SLOT (showPluginWidget (IPluginFactory *, IPlugin *,
                                                 Project *, int)));
}

void
tst_ModuleProject::cleanupTestCase ()
{
  ProjectControl::releaseInstance ();
  pjControl = nullptr;
  LanguageControl::releaseInstance ();
  lgControl = nullptr;
  PluginControl::releaseInstance ();
  pgControl = nullptr;

  QString projectDir = resourceDir + QDir::separator () + "projects";
  QDir docDir (projectDir);
  docDir.setFilter (QDir::Files | QDir::NoSymLinks);
  QFileInfoList list = docDir.entryInfoList ();

  for (int i = 0; i != list.size (); i++)
  {
    QFileInfo fileInfo = list.at (i);
    cout << "Trying to remove " << fileInfo.absoluteFilePath ().toStdString ();
    QFile file (fileInfo.absoluteFilePath ());
    file.remove ();
  }
}

void
tst_ModuleProject::init ()
{
#ifdef Q_WS_MAC
  QString filename = profileDir + QDir::separator () + "NCL"
                     + QDir::separator () + "libNCLLanguageProfile.dylib";
#elif WIN32
// TODO:
#else
  QString filename = profileDir + QDir::separator () + "NCL"
                     + QDir::separator () + "libNCLLanguageProfile.so";

// cout << filename.toStdString();
#endif

  QVERIFY (lgControl->loadProfile (filename));
}

void
tst_ModuleProject::cleanup ()
{
  lgControl->removeProfile (NCL);
}

void
tst_ModuleProject::importFromExistingNCL_data ()
{
  QTest::addColumn<QString> ("docFileName");
  QTest::addColumn<QString> ("projectFileName");
  QTest::addColumn<int> ("size");
  QTest::addColumn<int> ("numPlugins");

  QDir docDir (resourceDir);
  docDir.setFilter (QDir::Files | QDir::NoSymLinks);
  docDir.setSorting (QDir::Size | QDir::Reversed);

  QFileInfoList list = docDir.entryInfoList ();

  for (int k = 1; k <= pluginList.size (); k++)
  {
    for (int i = 0; i != list.size (); i++)
    {
      QFileInfo docFile = list.at (i);
      if (docFile.completeSuffix () != "ncl")
        continue;
      QString absDocFile = docFile.absoluteFilePath ();
      QString absProjFile = docFile.absolutePath () + QDir::separator ()
                            + "projects" + QDir::separator ()
                            + docFile.baseName () + ".cpr";
      int size = docFile.size ();
      QString teste = "teste" + QString::number (k);
      QTest::newRow (teste.toStdString ().c_str ())
          << absDocFile << absProjFile << size << k;
      // if(i==1) break;
    }
  }
}

void
tst_ModuleProject::importFromExistingNCL ()
{
  QFETCH (QString, docFileName);
  QFETCH (QString, projectFileName);
  QFETCH (int, size);
  QFETCH (int, numPlugins);

  for (int i = 0; i < numPlugins; i++)
  {
    QString pluginName = pluginList.at (i);
    pgControl->loadPlugin (pluginName);
  }

  ofstream myfile;
  QString filename = "output/composer_";
  filename += QString::number (numPlugins);
  filename += "_plugins_importNCL_incremental.txt";
  myfile.open (filename.toStdString ().c_str ());

  timeval begin, end;
  // QVERIFY(pjControl->launchProject(projectFileName));
  gettimeofday (&begin, nullptr);
  pjControl->importFromDocument (docFileName, projectFileName);
  gettimeofday (&end, nullptr);
  long long int interval = TestUtil::timeval_subtract_micro (begin, end);
  cout << numPlugins << " " << size << " " << (double)interval / 1000.0 << " ";
  gettimeofday (&begin, nullptr);
  pjControl->saveProject (projectFileName);
  gettimeofday (&end, nullptr);
  interval = TestUtil::timeval_subtract_micro (begin, end);
  cout << (double)interval / 1000.0 << endl;
  QApplication::processEvents ();
  //  showWidgets.redraw();
  QVERIFY (pjControl->closeProject (projectFileName));
  myfile.close ();
}

void
tst_ModuleProject::importNCLForEachPlugin_data ()
{
  QTest::addColumn<QString> ("docFileName");
  QTest::addColumn<QString> ("projectFileName");
  QTest::addColumn<int> ("size");
  QTest::addColumn<int> ("pluginPos");

  QDir docDir (resourceDir);
  docDir.setFilter (QDir::Files | QDir::NoSymLinks);
  docDir.setSorting (QDir::Size | QDir::Reversed);

  QFileInfoList list = docDir.entryInfoList ();

  for (int k = 0; k <= pluginList.size (); k++)
  {
    for (int i = 0; i < list.size (); i++)
    {
      QFileInfo docFile = list.at (i);
      if (docFile.completeSuffix () != "ncl")
        continue;
      QString absDocFile = docFile.absoluteFilePath ();
      QString absProjFile = docFile.absolutePath () + QDir::separator ()
                            + "projects" + QDir::separator ()
                            + docFile.baseName () + ".cpr";
      int size = docFile.size ();
      QString teste = "teste" + k;
      QTest::newRow (teste.toStdString ().c_str ())
          << absDocFile << absProjFile << size << k;
      // if(i==1) break;
    }
  }
}

void
tst_ModuleProject::importNCLForEachPlugin ()
{
  QFETCH (QString, docFileName);
  QFETCH (QString, projectFileName);
  QFETCH (int, size);
  QFETCH (int, pluginPos);

  QString pluginName = pluginList.at (pluginPos);
  pgControl->loadPlugin (pluginName);

  ofstream myfile;
  QString filename = "output/composer_";
  filename += QString::number (pluginPos);
  filename += "_plugin_importForEachplugin.txt";
  myfile.open (filename.toStdString ().c_str ());

  timeval begin, end;
  gettimeofday (&begin, nullptr);
  pjControl->importFromDocument (docFileName, projectFileName);
  gettimeofday (&end, nullptr);
  long long int interval = TestUtil::timeval_subtract_micro (begin, end);
  myfile << pluginName.mid (pluginName.lastIndexOf ("/") + 1)
                .toStdString ()
                .c_str ()
         << " " << size << " " << (double)interval / 1000.0 << " ";
  gettimeofday (&begin, nullptr);
  pjControl->saveProject (projectFileName);
  gettimeofday (&end, nullptr);
  interval = TestUtil::timeval_subtract_micro (begin, end);
  myfile << (double)interval / 1000.0 << endl;
  QVERIFY (pjControl->closeProject (projectFileName));

  myfile.close ();
}
