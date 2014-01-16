#include "qnstnode.h"

#include <QDebug>

QnstNode::QnstNode(QnstEntity* parent)
  : QnstEntityWithEdges(parent)
{
  setnstType(Qnst::Node);
  setnstSubtype(Qnst::NoSubtype);

  hover = false;
}

QnstNode::~QnstNode()
{

}

void QnstNode::fit(qreal padding)
{
  qreal top = getTop();
  qreal left = getLeft();
  qreal width = getWidth();
  qreal height = getHeight();

  qreal nextTop = top;
  qreal nextLeft = left;
  qreal nextWidth = width;
  qreal nextHeight = height;

  foreach(QnstEntity* entity, getnstChildren())
  {
    if (entity->getnstType() == Qnst::Node)
    {
      if ((entity->getTop()-4) + top < nextTop + padding)
      {
        nextTop = (entity->getTop()-4) + top - padding;
      }

      if ((entity->getLeft()-4) + left < nextLeft + padding)
      {
        nextLeft = (entity->getLeft()-4) + left - padding;
      }

      if ((entity->getLeft()-4) + entity->getWidth() > nextWidth - padding)
      {
        nextWidth = (entity->getLeft()-4) + entity->getWidth() + padding;
      }

      if ((entity->getTop()-4) + entity->getHeight() > nextHeight - padding)
      {
        nextHeight = (entity->getTop()-4) + entity->getHeight() + padding;
      }
    }
  }

  if (nextWidth != width)
    setWidth(nextWidth);

  if (nextHeight != height)
    setHeight(nextHeight);

  if (nextTop != top)
  {
    foreach(QnstEntity* entity, getnstChildren())
    {
      if (entity->getnstType() == Qnst::Node)
      {
        entity->setTop(entity->getTop() + (top - nextTop));
      }
    }

    setHeight(getHeight() + (top - nextTop));
    setTop(nextTop);
  }

  if (nextLeft != left)
  {
    foreach(QnstEntity* entity, getnstChildren())
    {
      if (entity->getnstType() == Qnst::Node)
      {
        entity->setLeft(entity->getLeft() + (left - nextLeft));
      }
    }

    setWidth(getWidth() + (left - nextLeft));
    setLeft(nextLeft);
  }

  QnstNode* parent = (QnstNode*) getnstParent();

  if (parent != NULL)
    parent->fit(padding);
}

void QnstNode::inside()
{
  QnstEntity* parent = getnstParent();

  if (parent != NULL)
  {
    QPointF pa(getLeft()+getWidth()/2, getTop()+getHeight()/2);
    QPointF pb(parent->getWidth()/2, parent->getHeight()/2);

    QLineF line(pa, pb);

    qreal n = 0;

    qreal i = 0.0;

    setSelectable(false);
    update();

    while(!collidesWithItem(parent,Qt::ContainsItemShape))
    {
      i += 0.01;

      setTop(getTop()+line.pointAt(i).y()-pa.y());
      setLeft(getLeft()+line.pointAt(i).x()-pa.x());

      if (++n > 1000) // avoid inifinity loop
      {
        n = -1;
        break;
      }
    }

    if (n < 0)
    {
      setTop(pb.x()-getHeight()/2);
      setLeft(pb.y()-getWidth()/2);
    }

    setSelectable(true); update();
  }
}


void QnstNode::adjust(bool avoidCollision)
{
  foreach(QnstEntity* entity, getnstChildren())
  {
    if (entity->getnstType() != Qnst::Edge)
    {
      entity->adjust(false);
    }
  }

  if(getnstParent() != NULL)
  {
    if (avoidCollision){
      int colliding;
      int maxInter = 10, inter = 0;
      do
      {
        if(inter > maxInter) break;
        inter++;

        colliding = false;
        foreach(QnstEntity *entity,
                getnstParent()->getnstChildren())
        {
          if(this != entity && entity->getnstSubtype() >= Qnst::Node &&
             entity->getnstSubtype() <= Qnst::Switch)
          {
            qreal n = 0;
            qreal i = 0.0;

            entity->setSelectable(false); update();
            // check collision
            while(collidesWithItem(entity, Qt::IntersectsItemBoundingRect))
            {

              QPointF pa(getLeft()+getWidth()/2, getTop()+getHeight()/2);
              QPointF pb(entity->getWidth()/2, entity->getHeight()/2);

              QLineF line(pa, pb);

              line.setAngle(qrand()%360);

              i += (double)(qrand()%100)/10000.0;

              setTop(getTop()+line.pointAt(i/2).y()-pa.y());
              setLeft(getLeft()+line.pointAt(i/2).x()-pa.x());

              if (++n > 1000){
                n = -1; break;
              }
            }

            inside();

            entity->setSelectable(true); update();
          }
        }

        foreach(QnstEntity *entity,
                getnstParent()->getnstChildren())
        {
          if(collidesWithItem(entity, Qt::IntersectsItemBoundingRect))
          {
            colliding = true;
          }
        }
      }
      while(colliding);
    }
  }

  inside();


//  foreach(QnstEntity* entity, getnstGraphicsEdges())
//  {
//      entity->adjust();
//  }

  if (scene() != NULL)
    scene()->update();
}

void QnstNode::move(QGraphicsSceneMouseEvent* event)
{
  // setting
  qreal x = getLeft();
  qreal y = getTop();

  QnstEntity* parent = getnstParent();

  // setting minimal position
  qreal minx;
  qreal miny;

  if (parent != NULL)
  {
    minx = 4;
    miny = 4;
  }
  else
  {
    minx = 0;
    miny = 0;
  }

  // setting maximal position
  qreal maxx;
  qreal maxy;

  if (parent != NULL)
  {
    maxx = parent->getWidth() - getWidth() - 4;
    maxy = parent->getHeight() - getHeight() - 4;
  }
  else
  {
    maxx = scene()->width() - getWidth();
    maxy = scene()->height() - getHeight();
  }

  // setting delta
  qreal dx = event->pos().x() - getPressLeft(); // (x1 - x0)
  qreal dy = event->pos().y() - getPressTop();  // (y1 - y0)

  // setting next position
  qreal nextx = x + dx;
  qreal nexty = y + dy;

  // moving
  setMoveTop(nexty);
  setMoveLeft(nextx);


  scene()->update();
}

void QnstNode::resize(QGraphicsSceneMouseEvent* event)
{
  // setting
  qreal x = getLeft();
  qreal y = getTop();
  qreal w = getWidth();
  qreal h = getHeight();

  QnstEntity* parent = getnstParent();

  // setting minimal bounds
  qreal minx;
  qreal miny;
  qreal minw;
  qreal minh;

  if (parentItem() != NULL)
  {
    minx = 4;
    miny = 4;
    minw = -1; // not used
    minh = -1; // not used
  }
  else
  {
    minx = 0;
    miny = 0;
    minw = -1; // not used
    minh = -1; // not used
  }

  // setting maximal bounds
  qreal maxx;
  qreal maxy;
  qreal maxw;
  qreal maxh;

  if (parentItem() != NULL)
  {
    maxx = parent->getWidth() - getWidth() - 4;
    maxy = parent->getHeight() - getHeight() - 4;
    maxw = parent->getWidth() - 4;
    maxh = parent->getHeight() - 4;
  }
  else
  {
    maxx = scene()->width() - getWidth();
    maxy = scene()->height() - getHeight();
    maxw = scene()->width();
    maxh = scene()->height();
  }

  // setting delta
  qreal dx = event->pos().x() - getPressLeft();    // (x1 - x0)
  qreal dy = event->pos().y() - getPressTop();     // (y1 - y0)
  qreal dw = -dx;
  qreal dh = -dy;

  // setting next bounds
  qreal nextx = x + dx;
  qreal nexty = y + dy;
  qreal nextw = w + dw;
  qreal nexth = h + dh;

  // adjusting
  switch(getResizeType())
  {
    case Qnst::TopLeft:
    {
      break;
    }

    case Qnst::Top:
    {
      nextx = x; // fixed x
      nextw = w; // fixed width

      break;
    }

    case Qnst::TopRight:
    {
      nextx = x; // fixed x
      nextw = w - dw;

      break;
    }

    case Qnst::Right:
    {
      nextx = x; // fixed x
      nextw = w - dw;

      nexty = y; // fixed y
      nexth = h; // fixed height

      break;
    }

    case Qnst::BottomRight:
    {
      nextx = x; // fixed x
      nextw = w - dw;

      nexty = y; // fixed y
      nexth = h - dh;

      break;
    }

    case Qnst::Bottom:
    {
      nextx = x; // fixed x
      nextw = w; // fixed width

      nexty = y; // fixed y
      nexth = h - dh;

      break;
    }

    case Qnst::BottomLeft:
    {
      nexty = y; // fixed y
      nexth = h - dh;

      break;
    }

    case Qnst::Left:
    {
      nexty = y; // fixed y
      nexth = h; // fixed height

      break;
    }
  }

  // resizing
  setResizeTop(nexty);
  setResizeLeft(nextx);
  setResizeWidth(nextw);
  setResizeHeight(nexth);

  scene()->update();
}