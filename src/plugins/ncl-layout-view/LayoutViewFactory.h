/*
 * Copyright (C) 2011-2018 TeleMidia/PUC-Rio.
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
#ifndef QNLYCOMPOSERPLUGINFACTORY_H
#define QNLYCOMPOSERPLUGINFACTORY_H

#include <extensions/IPluginFactory.h>
using namespace cpr::core;

#include "LayoutViewPlugin.h"

class NCLLayoutViewFactory : public QObject,
                             public IPluginFactoryTpl<NCLLayoutViewPlugin>
{
  Q_OBJECT
  CPR_PLUGIN_METADATA ("br.puc-rio.telemidia.layout", "ncl-layout-view.json")

public:
  explicit NCLLayoutViewFactory (QObject *parent = 0);
  virtual ~NCLLayoutViewFactory () {}
};

#endif // QNLYCOMPOSERPLUGINFACTORY_H
