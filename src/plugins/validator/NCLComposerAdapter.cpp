/*
 * Copyright 2011-2013 Laws/UFMA.
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
 * License along with this library. If not, see
 * <http://www.gnu.org/licenses/>.
 */

#include "NCLComposerAdapter.h"

ComposerNCLAdapter::ComposerNCLAdapter ()
{
  GlobalSettings settings;
  settings.beginGroup ("languages");
  language = settings.value ("currentLanguage", QString ("en")).toString ();
  settings.endGroup ();
}

void
ComposerNCLAdapter::addElement (Entity *entity)
{
  Q_ASSERT (entity != nullptr);

  std::vector<Attribute> attributes = createVectorAttribute (entity);
  Entity *parent = static_cast<Entity *> (entity->parent ());

  if (parent && !idToVirtualId.count (parent->uid ())
      && parent->type () != "document")
  {
    addElement (parent);
  }

  virtualId virtualId
      = nclModel.addElement (entity->type ().toStdString (), attributes);

  if (virtualId != "")
    idToVirtualId.insert (entity->uid (), virtualId);

  if (parent && parent->type () != "document")
  {
    nclModel.addChild (idToVirtualId[entity->parentUid ()], virtualId);
  }

  ModelElement *el = nclModel.element (virtualId);
  if (el)
  {
    el->setData (entity);
  }
}

void
ComposerNCLAdapter::changeElement (Entity *entity)
{
  virtualId virtualId = idToVirtualId[entity->uid ()];

  if (virtualId == "")
    return;

  std::vector<Attribute> attributes = createVectorAttribute (entity);

  nclModel.editElement (virtualId, attributes);
}

void
ComposerNCLAdapter::removeElement (QString entityID)
{
  virtualId virtualId = idToVirtualId[entityID];

  if (virtualId != "")
  {
    nclModel.removeElement (virtualId);
  }
}

std::vector<std::pair<void *, std::string> >
ComposerNCLAdapter::validate ()
{
  std::vector<std::pair<void *, std::string> > msgs
      = Validator::validate (nclModel, language.toStdString ());

  nclModel.clearMarkedElements ();

  return msgs;
}

std::vector<Attribute>
ComposerNCLAdapter::createVectorAttribute (Entity *entity)
{
  QMap<QString, QString> attrs = entity->attrs ();

  std::vector<Attribute> attributes;

  foreach (const QString &key, attrs.keys ())
  {
    QString name = key;
    QString value = attrs[key];

    Attribute attr (name.toStdString (), value.toStdString ());

    attributes.push_back (attr);
  }

  return attributes;
}
