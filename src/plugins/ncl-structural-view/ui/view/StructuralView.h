#ifndef STRUCTURALVIEW_H
#define STRUCTURALVIEW_H

#include <QGraphicsView>

#include <QDomDocument>
#include <QDomElement>

#include <QKeyEvent>
#include <QMouseEvent>
#include <QResizeEvent>
#include <QWheelEvent>

#include <QDir>
#include <QUndoStack>

#include "Commands.h"

#include "StructuralBind.h"
#include "StructuralComposition.h"
#include "StructuralContent.h"
#include "StructuralEntity.h"
#include "StructuralInterface.h"
#include "StructuralLink.h"
#include "StructuralLinkDialog.h"
#include "StructuralLinkTool.h"
#include "StructuralMinimap.h"
#include "StructuralScene.h"

namespace util = StructuralUtil;
class StructuralMinimap;

class StructuralView : public QGraphicsView
{
  Q_OBJECT

public:
  constexpr static int ZOOM_MIN = ST_DEFAULT_SCENE_ZOOM_MIN;
  constexpr static int ZOOM_MAX = ST_DEFAULT_SCENE_ZOOM_MAX;
  constexpr static int ZOOM_ORIGINAL = ST_DEFAULT_SCENE_ZOOM_ORIGINAL;
  constexpr static int ZOOM_STEP = ST_DEFAULT_SCENE_ZOOM_STEP;

  StructuralView (QWidget *parent = 0);
  virtual ~StructuralView () {}

  StructuralScene *getScene ();
  StructuralLinkDialog *getDialog ();

  StructuralMode getMode () const;
  void setMode (StructuralMode mode);

  void setError (const QString &uid, const QString &error);

  void clearErrors ();

  StructuralMenu *
  getMenu ()
  {
    return _menu;
  }

public slots:
  // External methods
  void createEntity (StructuralType type, QStrMap prop = QStrMap (),
                     QStrMap stgs = QStrMap ());

  void changeEntity (QString uid, QStrMap props, QStrMap prev, QStrMap stgs);

  void removeEntity (QString uid, QStrMap settings);

  // "Internal" methods
  void insert (QString uid, QString parent, QStrMap properties,
               QStrMap settings);
  void remove (QString uid, QStrMap settings);
  void change (QString uid, QStrMap properties, QStrMap previous,
               QStrMap settings);
  void select (QString uid, QStrMap settings);

  void move (QString uid, QString parent, QStrMap properties,
             QStrMap settings);

  void zoomIn ();
  void zoomOut ();
  void zoomOriginal ();
  void snapshot ();
  void toggleMinimapVisibility ();

  // FIXME: These methods should not be part of StructuralView
  void undo ();
  void redo ();

  void performAutostart ();
  void performPointer ();
  void performLink ();
  void performDelete ();

  void performCut ();
  void performCopy ();
  void performPaste ();

#ifdef WITH_GRAPHVIZ
  void performAutoAdjust ();
#endif

  void performInsert (StructuralType type, QStrMap properties);

  void performLinkDialog (StructuralLink *entity);
  void performBindDialog (StructuralBind *entity);

  void clean ();

  void adjustReferences (StructuralEntity *entity);

signals:
  void inserted (QString uid, QString _parent, QStrMap properties,
                 QStrMap settings);
  void removed (QString uid, QStrMap settings);
  void changed (QString uid, QStrMap properties, QStrMap previous,
                QStrMap settings);
  void selected (QString uid, QStrMap settings);

  void canUndoChanged (bool state);
  void canRedoChanged (bool state);

  void canCutChanged (bool state);
  void canCopyChanged (bool state);
  void canPasteChanged (bool state);
  void canDeleteChanged (bool state);

  void switchedSnapshot (bool state);
  void switchedPointer (bool state);
  void switchedLink (bool state);

  void zoomChanged (int zoom);
  void canAddBody (bool state);

  void updateRequested ();

protected:
  virtual void mouseMoveEvent (QMouseEvent *event);
  virtual void mousePressEvent (QMouseEvent *event);
  virtual void mouseReleaseEvent (QMouseEvent *event);

  virtual void keyPressEvent (QKeyEvent *event);
  virtual void keyReleaseEvent (QKeyEvent *event);

  virtual void wheelEvent (QWheelEvent *event);

  virtual void dragEnterEvent (QDragEnterEvent *event);
  virtual void dragMoveEvent (QDragMoveEvent *event);
  virtual void dropEvent (QDropEvent *event);

  virtual void resizeEvent (QResizeEvent *event);

private:
  void createLink (StructuralEntity *tail, StructuralEntity *head);
  void createBind (StructuralEntity *tail, StructuralEntity *head,
                   const QString &role = "", const QString &code = "");
  void createReference (StructuralEntity *tail, StructuralEntity *head);

  QString getNewId (StructuralEntity *entity);
  qreal getNewAngle (StructuralBind *edge);

  void adjustProperties (StructuralEntity *entity);

#ifdef WITH_GRAPHVIZ
  void adjustLayout ();
  void adjustLayout (StructuralEntity *entity, const QString &code);
#endif

  bool isChild (StructuralEntity *entity, StructuralEntity *parent);

  void paste (StructuralEntity *entity, StructuralEntity *parent);
  void paste (StructuralEntity *entity, StructuralEntity *parent,
              const QString &code, bool adjust);

  StructuralMode _mode;

  int _zoom; // an integer in %  (varing from ZOOM_MIN to ZOOM_MAX)
  bool _linking;

  StructuralEntity *_linkingTail;
  StructuralEntity *_linkingHead;

  QString _selected;

  StructuralEntity *_clipboard;
  QStrMap _clipboardRefs;

  QUndoStack _commands;

  StructuralMinimap *_minimap;
  StructuralMenu *_menu;
  StructuralLinkDialog *_dialog;
  StructuralScene *_scene;
  StructuralLinkTool *_tool;
};

#endif // STRUCTURALVIEW_H