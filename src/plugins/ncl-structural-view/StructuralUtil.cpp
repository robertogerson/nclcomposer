#include "StructuralUtil.h"

#include <QUuid>

#include "StructuralEdge.h"
#include "StructuralView.h"

#include "util/Utilities.h"

Q_LOGGING_CATEGORY (CPR_PLUGIN_STRUCT, "cpr.plugin.struct")

namespace StructuralUtil
{
QString
createUid ()
{
  return QUuid::createUuid ().toString ();
}

QMap<QString, QString>
createSettings (bool undo, bool notify)
{
  return createSettings ((undo ? ST_VALUE_TRUE : ST_VALUE_FALSE),
                         (notify ? ST_VALUE_TRUE : ST_VALUE_FALSE),
                         createUid ());
}

QMap<QString, QString>
createSettings (const QString &undo, const QString &notify,
                const QString &code)
{
  QMap<QString, QString> sts;

  if (undo.isEmpty ())
    sts.insert (ST_SETTINGS_UNDO, ST_VALUE_TRUE);
  else
    sts.insert (ST_SETTINGS_UNDO, undo);

  if (notify.isEmpty ())
    sts.insert (ST_SETTINGS_NOTIFY, ST_VALUE_TRUE);
  else
    sts.insert (ST_SETTINGS_NOTIFY, notify);

  if (code.isEmpty ())
    sts.insert (ST_SETTINGS_CODE, createUid ());
  else
    sts.insert (ST_SETTINGS_CODE, code);

  return sts;
}

QMap<QString, QString>
createCoreTranslations (StructuralType type)
{
  QMap<QString, QString> transls;

  switch (type)
  {
    case Structural::Body:
    {
      transls = { { NCL_ATTR_ID, ST_ATTR_ENT_ID } };

      break;
    }

    case Structural::Context:
    case Structural::Switch:
    {
      transls = { { NCL_ATTR_ID, ST_ATTR_ENT_ID },
                  { NCL_ATTR_REFER, ST_ATTR_REFERENCE_REFER_ID } };

      break;
    }

    case Structural::Media:
    {
      transls = { { NCL_ATTR_ID, ST_ATTR_ENT_ID },
                  { NCL_ATTR_REFER, ST_ATTR_REFERENCE_REFER_ID },
                  { NCL_ATTR_INSTANCE, ST_ATTR_NODE_INSTANCE },
                  { NCL_ATTR_TYPE, ST_ATTR_NODE_TYPE },
                  { NCL_ATTR_SRC, ST_ATTR_NODE_SRC },
                  { NCL_ATTR_DESCRIPTOR, NCL_ATTR_DESCRIPTOR } };
      break;
    }

    case Structural::Port:
    {
      transls = { { NCL_ATTR_ID, ST_ATTR_ENT_ID },
                  { NCL_ATTR_COMPONENT, ST_ATTR_REFERENCE_COMPONENT_ID },
                  { NCL_ATTR_INTERFACE, ST_ATTR_REFERENCE_INTERFACE_ID } };

      break;
    }

    case Structural::Property:
    {
      transls = { { NCL_ATTR_NAME, ST_ATTR_ENT_ID },
                  { NCL_ATTR_VALUE, NCL_ATTR_VALUE },
                  { NCL_ATTR_EXTERNABLE, NCL_ATTR_EXTERNABLE } };
      break;
    }

    case Structural::Area:
    {
      transls = { { NCL_ATTR_ID, ST_ATTR_ENT_ID },
                  { NCL_ATTR_COORDS, NCL_ATTR_COORDS },
                  { NCL_ATTR_BEGIN, NCL_ATTR_BEGIN },
                  { NCL_ATTR_END, NCL_ATTR_END },
                  { NCL_ATTR_BEGINTEXT, NCL_ATTR_BEGINTEXT },
                  { NCL_ATTR_ENDTEXT, NCL_ATTR_ENDTEXT },
                  { NCL_ATTR_BEGINPOSITION, NCL_ATTR_BEGINPOSITION },
                  { NCL_ATTR_ENDPOSITION, NCL_ATTR_ENDPOSITION },
                  { NCL_ATTR_FIRST, NCL_ATTR_FIRST },
                  { NCL_ATTR_LAST, NCL_ATTR_LAST },
                  { NCL_ATTR_LABEL, NCL_ATTR_LABEL },
                  { NCL_ATTR_CLIP, NCL_ATTR_CLIP } };

      break;
    }

    case Structural::SwitchPort:
    {
      transls = { { NCL_ATTR_ID, ST_ATTR_ENT_ID } };

      break;
    }

    case Structural::Link:
    {
      transls = { { NCL_ATTR_ID, ST_ATTR_ENT_ID },
                  { NCL_ATTR_XCONNECTOR, ST_ATTR_REFERENCE_XCONNECTOR_ID } };

      break;
    }

    case Structural::Bind:
    {
      transls = { { NCL_ATTR_ROLE, ST_ATTR_ENT_ID },
                  { NCL_ATTR_XCONNECTOR, ST_ATTR_REFERENCE_XCONNECTOR_ID },
                  { NCL_ATTR_COMPONENT, ST_ATTR_REFERENCE_COMPONENT_ID },
                  { NCL_ATTR_INTERFACE, ST_ATTR_REFERENCE_INTERFACE_ID },
                  { NCL_ATTR_DESCRIPTOR, NCL_ATTR_DESCRIPTOR } };

      break;
    }

    case Structural::Mapping:
    {
      transls = { { NCL_ATTR_COMPONENT, ST_ATTR_REFERENCE_COMPONENT_ID },
                  { NCL_ATTR_INTERFACE, ST_ATTR_REFERENCE_INTERFACE_ID } };

      break;
    }

    default:
      CPR_ASSERT_NOT_REACHED ();
      break;
  }

  return transls;
}

QMap<QString, QString>
createPluginTranslations (StructuralType type)
{
  QMap<QString, QString> transl;
  QMap<QString, QString> inverted = createCoreTranslations (type);

  for (const QString &key : inverted.keys ())
    transl[inverted.value (key)] = key;

  return transl;
}

static const std::map<Structural::Category, QString> _categoryToStr
    = { { Structural::Node, "node" },
        { Structural::Edge, "edge" },
        { Structural::Interface, "interface" },
        { Structural::NoCategory, "" } };

const std::map<QString, Structural::Category> _strToCategory
    = invert<QString, Structural::Category> (_categoryToStr);

QString
categoryToStr (StructuralCategory category)
{
  if (_categoryToStr.count (category))
    return _categoryToStr.at (category);
  else
    return "";
}

StructuralCategory
strToCategory (const QString &category)
{
  if (_strToCategory.count (category))
    return _strToCategory.at (category);
  else
    return Structural::NoCategory;
}

static const std::map<Structural::Type, QString> _typeToStr
    = { { Structural::Media, "media" },
        { Structural::Body, "body" },
        { Structural::Context, "context" },
        { Structural::Switch, "switch" },
        { Structural::Port, "port" },
        { Structural::SwitchPort, "switchPort" },
        { Structural::Area, "area" },
        { Structural::Property, "property" },
        { Structural::Link, "link" },
        { Structural::Bind, "bind" },
        { Structural::Reference, "reference" },
        { Structural::Mapping, "mapping" },
        { Structural::NoType, "" } };

static const std::map<QString, Structural::Type> _strToType
    = invert<QString, Structural::Type> (_typeToStr);

QString
typeToStr (StructuralType type)
{
  if (_typeToStr.count (type))
    return _typeToStr.at (type);
  else
    return "";
}

StructuralType
strToType (const QString &type)
{
  if (_strToType.count (type))
    return _strToType.at (type);
  else
    return Structural::NoType;
}

static const std::map<Structural::Role, QString> _roleToStr
    = { { Structural::onBegin, "onBegin" },
        { Structural::onEnd, "onEnd" },
        { Structural::onSelection, "onSelection" },
        { Structural::onResume, "onResume" },
        { Structural::onPause, "onPause" },
        { Structural::onBeginAttribution, "onBeginAttribution" },
        { Structural::onEndAttribution, "onEndAttribution" },
        { Structural::onPauseAttribution, "onPauseAttribution" },
        { Structural::onResumeAttribution, "onResumeAttribution" },
        { Structural::Start, "start" },
        { Structural::Stop, "stop" },
        { Structural::Resume, "resume" },
        { Structural::Pause, "pause" },
        { Structural::Set, "set" },
        { Structural::NoRole, "" } };

static const std::map<QString, Structural::Role> _strToRole
    = invert<QString, Structural::Role> (_roleToStr);

QString
roleToString (StructuralRole role)
{
  if (_roleToStr.count (role))
    return _roleToStr.at (role);
  else
    return "";
}

StructuralRole
strToRole (const QString &role)
{
  if (_strToRole.count (role))
    return _strToRole.at (role);
  else
    return Structural::NoRole;
}

static const std::map<Structural::MimeType, QString> _mimeToStr
    = { { Structural::Text, "text" },   { Structural::Image, "image" },
        { Structural::Audio, "audio" }, { Structural::Video, "video" },
        { Structural::HTML, "html" },   { Structural::NCL, "ncl" },
        { Structural::NCLua, "nclua" }, { Structural::Settings, "settings" },
        { Structural::Time, "time" },   { Structural::NoMimeType, "" } };

static const std::map<QString, Structural::MimeType> _strToMime
    = invert<QString, Structural::MimeType> (_mimeToStr);

QString
mimeToStr (StructuralMimeType mime)
{
  if (_mimeToStr.count (mime))
    return _mimeToStr.at (mime);
  else
    return "media";
}

StructuralMimeType
strToMime (const QString &mime)
{
  if (_strToMime.count (mime))
    return _strToMime.at (mime);
  else
    return Structural::NoMimeType;
}

static const std::map<Structural::Type, QString> _entitiesIcon
    = { { Structural::Media, ":/icon/media" },
        { Structural::Body, ":/icon/body" },
        { Structural::Context, ":/icon/context" },
        { Structural::Switch, ":/icon/switch" },
        { Structural::Port, ":/icon/port-mini" },
        { Structural::SwitchPort, ":/icon/switchport-mini" },
        { Structural::Area, ":/icon/area-mini" },
        { Structural::Property, ":/icon/property-mini" },
        { Structural::Link, "" },
        { Structural::Bind, "" },
        { Structural::Reference, "" },
        { Structural::Mapping, "" },
        { Structural::NoType, "" } };

QString
getIcon (StructuralType type)
{
  if (_entitiesIcon.count (type))
    return _entitiesIcon.at (type);
  else
    return "";
}

const std::map<Structural::Type, QString> _entitiesColor
    = { { Structural::Media, "" },
        { Structural::Body, "#EEEEEE" },
        { Structural::Context, "#F4E4CC" },
        { Structural::Switch, "#C6E2FF" },
        { Structural::Port, "" },
        { Structural::SwitchPort, "" },
        { Structural::Area, "" },
        { Structural::Property, "" },
        { Structural::Link, "#000000" },
        { Structural::Bind, "#000000" },
        { Structural::Reference, "#000000" },
        { Structural::Mapping, "#5C0099" },
        { Structural::NoType, "" } };

QString
getColor (StructuralType type)
{
  if (_entitiesColor.count (type))
    return _entitiesColor.at (type);
  else
    return "";
}

static const std::map<Structural::Type, QString> _entitiesPrefix
    = { { Structural::Media, "m" },       { Structural::Body, "b" },
        { Structural::Context, "ctx" },   { Structural::Switch, "swt" },
        { Structural::Port, "p" },        { Structural::SwitchPort, "swtp" },
        { Structural::Area, "a" },        { Structural::Property, "p" },
        { Structural::Link, "l" },        { Structural::Bind, "bd" },
        { Structural::Reference, "ref" }, { Structural::Mapping, "map" },
        { Structural::NoType, "e" } };

QString
getPrefix (StructuralType type)
{
  if (_entitiesPrefix.count (type))
    return _entitiesPrefix.at (type);
  else
    return "e";
}

QString
getTooltip (StructuralType type, const QString &title, const QString &info,
            const QString &warning, const QString &error, const QString &extra)
{
  QString tooltip;

  // Adding type
  tooltip += typeToStr (type);
  tooltip += " ";

  // Adding title
  if (!title.isEmpty ())
    tooltip += "(" + title + ")";
  else
    tooltip += "(?)";

  tooltip += " ";

  // Adding extra
  if (type == Structural::Link)
  {
    if (!extra.isEmpty ())
      tooltip += ": " + extra;
    else
      tooltip += ": Unknow";

    tooltip += " ";
  }

  // Adding messages
  if (!error.isEmpty ())
    tooltip += "- Error: " + error;
  else if (!warning.isEmpty ())
    tooltip += "- Warning: " + warning;
  else if (!info.isEmpty ())
    tooltip += "- Info: " + info;

  // Formating
  tooltip[0] = tooltip[0].toUpper ();

  return tooltip;
}

static const std::map<Structural::MimeType, QString> _mimeIcon
    = { { Structural::Text, ":/icon/media-text" },
        { Structural::Image, ":/icon/media-image" },
        { Structural::Audio, ":/icon/media-audio" },
        { Structural::Video, ":/icon/media-video" },
        { Structural::HTML, ":/icon/media-text-html" },
        { Structural::NCL, ":/icon/media-ncl" },
        { Structural::NCLua, ":/icon/media-nclua" },
        { Structural::Settings, ":/icon/media-settings" },
        { Structural::Time, ":/icon/media-time" },
        { Structural::NoMimeType, ":/icon/media" } };

QString
getMimeTypeIcon (StructuralMimeType type)
{
  if (_mimeIcon.count (type))
    return _mimeIcon.at (type);
  else
    return ":/icon/media";
}

QString
getMimeTooltip (StructuralMimeType mime, const QString &title,
                const QString &info, const QString &warning,
                const QString &error, const QString &extra)
{
  Q_UNUSED (extra);

  QString tooltip = mimeToStr (mime) + " ";

  if (!title.isEmpty ())
    tooltip += "(" + title + ")";
  else
    tooltip += "(?)";

  tooltip += " ";

  if (!error.isEmpty ())
    tooltip += "- Error: " + error;
  else if (!warning.isEmpty ())
    tooltip += "- Warning: " + warning;
  else if (!info.isEmpty ())
    tooltip += "- Info: " + info;

  tooltip[0] = tooltip[0].toUpper ();

  return tooltip;
}

static const std::map<QString, Structural::MimeType> _mimeExtension
    = { { "txt", Structural::Text },    { "png", Structural::Image },
        { "jpg", Structural::Image },   { "jpeg", Structural::Image },
        { "gif", Structural::Image },   { "mp3", Structural::Audio },
        { "wav", Structural::Audio },   { "mp4", Structural::Video },
        { "mpeg4", Structural::Video }, { "mpeg", Structural::Video },
        { "mpg", Structural::Video },   { "mov", Structural::Video },
        { "avi", Structural::Video },   { "mkv", Structural::Video },
        { "htm", Structural::HTML },    { "html", Structural::HTML },
        { "ncl", Structural::NCL },     { "lua", Structural::NCLua } };

Structural::MimeType
getMimeByExtension (const QString &ext)
{
  if (_mimeExtension.count (ext))
    return _mimeExtension.at (ext);
  else
    return Structural::NoMimeType;
}

static const std::map<Structural::Role, QString> _rolesIcon
    = { { Structural::onBegin, ":/icon/bind-onbegin" },
        { Structural::onEnd, ":/icon/bind-onend" },
        { Structural::onSelection, ":/icon/bind-onselection" },
        { Structural::onResume, ":/icon/bind-onresume" },
        { Structural::onPause, ":/icon/bind-onpause" },
        { Structural::onBeginAttribution, "" },
        { Structural::onEndAttribution, "" },
        { Structural::onPauseAttribution, "" },
        { Structural::onResumeAttribution, "" },
        { Structural::Start, ":/icon/bind-start" },
        { Structural::Stop, ":/icon/bind-stop" },
        { Structural::Resume, ":/icon/bind-resume" },
        { Structural::Pause, ":/icon/bind-pause" },
        { Structural::Set, ":/icon/bind-set" },
        { Structural::NoRole, "" } };

QString
getIcon (StructuralRole role)
{
  if (_rolesIcon.count (role))
    return _rolesIcon.at (role);
  else
    return "";
}

QVector<StructuralEntity *>
getNeighbors (StructuralEntity *ent)
{
  QVector<StructuralEntity *> neighbors;
  StructuralEntity *parent = ent->getParent ();

  if (parent)
  {
    neighbors = parent->getChildren ();
  }
  else if (!ST_OPT_WITH_BODY)
  {
    StructuralScene *scn = dynamic_cast<StructuralScene *> (ent->scene ());
    //    CPR_ASSERT_NON_NULL (scn);

    if (scn)
    {
      for (StructuralEntity *cur : scn->getEntities ().values ())
      {
        if (cur->getParent () == nullptr && cur != ent)
          neighbors += cur;
      }
    }
  }

  return neighbors;
}

QVector<StructuralEntity *>
getUpNeighbors (StructuralEntity *ent)
{
  QVector<StructuralEntity *> neighbors;

  StructuralEntity *parent = ent->getParent ();
  if (parent)
  {
    if (parent->getParent ())
    {
      neighbors += parent->getParent ()->getChildren ();
    }
    else if (!ST_OPT_WITH_BODY)
    {
      StructuralScene *scn = (StructuralScene *)ent->scene ();
      //      CPR_ASSERT_NON_NULL (scn);

      qWarning () << scn;
      if (scn)
      {
        for (StructuralEntity *cur : scn->getEntities ().values ())
        {
          if (cur->getParent () == nullptr && cur != ent)
            neighbors += cur;
        }
      }
    }
  }

  return neighbors;
}

bool
isCondition (StructuralRole role)
{
  return (role == Structural::onBegin || role == Structural::onBeginAttribution
          || role == Structural::onEnd || role == Structural::onEndAttribution
          || role == Structural::onPause
          || role == Structural::onPauseAttribution
          || role == Structural::onResume
          || role == Structural::onResumeAttribution
          || role == Structural::onSelection);
}

bool
isCondition (const QString &role)
{
  return (_strToRole.count (role) ? isCondition (_strToRole.at (role))
                                  : false);
}

bool
isAction (StructuralRole role)
{
  return (role != Structural::NoRole && !isCondition (role));
}

bool
isAction (const QString &role)
{
  return (_strToRole.count (role) && isAction (_strToRole.at (role)));
}

void
adjustEdges (StructuralEntity *ent)
{
  QVector<StructuralEntity *> relatives = getNeighbors (ent);
  relatives += getUpNeighbors (ent);

  for (StructuralEntity *rel : relatives)
  {
    if (rel->getCategory () == Structural::Edge)
    {
      StructuralEdge *edge = (StructuralEdge *)rel;

      if (edge->getTail () == ent || edge->getHead () == ent)
        edge->adjust (true);
    }
  }
}

QString
formatId (const QString &id)
{
  QString normalized = id.normalized (QString::NormalizationForm_KD);
  normalized.remove (QRegExp ("[^a-zA-Z_-\\.\\s]"));

  if (normalized.at (0).isDigit ())
    normalized = "_" + normalized;

  return normalized;
}

bool
validateKinship (StructuralType entT, StructuralType parentT)
{
#define _COMPOSITE_CHILDREN                                                   \
  Structural::Switch, Structural::Context, Structural::Media,                 \
      Structural::Port, Structural::Property, Structural::Link,               \
      Structural::Bind, Structural::Reference

  // ParentType -> allowed children types
  const static QMap<StructuralType, QList<StructuralType> > kinship = {
    { Structural::Body, { _COMPOSITE_CHILDREN } },
    { Structural::Context, { _COMPOSITE_CHILDREN } },
    { Structural::Switch,
      { _COMPOSITE_CHILDREN, Structural::SwitchPort, Structural::Mapping } },
    { Structural::Media, { Structural::Area } }
  };

  if (kinship.count (parentT))
    return kinship[parentT].count (entT);

  return false;
}
} // namespace