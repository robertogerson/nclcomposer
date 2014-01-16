#ifndef QNSTGRAPHICSNODE_H
#define QNSTGRAPHICSNODE_H

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneContextMenuEvent>
#include <QGraphicsSceneHoverEvent>

#include "qnstentity.h"
#include "qnstedge.h"

class QnstNode : public QnstEntityWithEdges
{
public:
  QnstNode(QnstEntity* parent = 0);

  ~QnstNode();

  virtual void fit(qreal padding);

  virtual void inside();

  virtual void adjust(bool avoidCollision = true);

protected:
  virtual void draw(QPainter* painter) = 0;
  virtual void delineate(QPainterPath* painter) const = 0;

  virtual void move(QGraphicsSceneMouseEvent* event);
  virtual void resize(QGraphicsSceneMouseEvent* event);

};

#endif // QNSTGRAPHICSNODE_H