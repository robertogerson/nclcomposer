/*
 * Copyright 2011-2013 TeleMidia/PUC-Rio.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library.  If not, see
 * <http://www.gnu.org/licenses/>.
 */
#ifndef NCLTEXTUALVIEWPLUGINFACTORY_H
#define NCLTEXTUALVIEWPLUGINFACTORY_H

#include "NCLTextualViewPlugin_global.h"

#include <extensions/IPluginFactory.h>
using namespace cpr::core;

#include "NCLTextualViewPlugin.h"
#include "NCLTextualViewPlugin_global.h"

namespace Ui
{
class TextPluginPreferencesWidget;
}

/*!
  \brief Handles the creation and deletion of NCLTextualView objects.
 */
class NCLTextualViewPluginFactory
    : public QObject,
      public IPluginFactoryTpl<NCLTextualViewPlugin>
{
  Q_OBJECT
  CPR_PLUGIN_METADATA ("ncl-textual-view.json")

public:
  NCLTextualViewPluginFactory ();

  QString
  id () const
  {
    return "br.puc-rio.telemidia.NCLTextualView";
  }
  QIcon
  icon () const
  {
    return QIcon (":/images/ncl.png");
  }

private:
  QFrame *_prefPageWidget;
  Ui::TextPluginPreferencesWidget *_prefPageUi;
};

#endif // NCLTEXTUALVIEWPLUGINFACTORY_H
