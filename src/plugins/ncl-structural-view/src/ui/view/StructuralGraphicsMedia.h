#ifndef QNSTGRAPHICSMEDIA_H
#define QNSTGRAPHICSMEDIA_H

#include <QGraphicsSceneDragDropEvent>
#include <QMimeData>
#include <QList>
#include <QUrl>
#include <QFileInfo>
#include <QKeyEvent>

#include "StructuralGraphicsNode.h"
#include "StructuralGraphicsProperty.h"
#include "StructuralGraphicsArea.h"

class StructuralGraphicsMedia : public StructuralGraphicsNode
{
  Q_OBJECT

public:
  StructuralGraphicsMedia(StructuralGraphicsEntity* parent = 0);

  ~StructuralGraphicsMedia();

  QString getIcon() const;

  void setSource(QString source);

  virtual void setnstType(QnstType type);

  QString getSource() const;

  QString getRefer() const;

  void setRefer(QString refer);

  QString getReferUID() const;

  void setReferUID(QString refetUID);

  QString getInstance() const;

  void setInstance(QString instance);

  virtual void updateToolTip();

  virtual void setProperties(const QMap <QString, QString> &properties);

  virtual void getProperties(QMap<QString, QString> &properties);

protected:
  virtual void draw(QPainter* painter);

  virtual void delineate(QPainterPath* painter) const;

  virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
  void createObjects();

  void createConnections();

  QString refer;

  QString referUID;

  QString instance;

  QString icon;

  QString source;

  bool enableDrag;
};

#endif // QNSTGRAPHICSMEDIA_H