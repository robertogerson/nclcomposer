#include "StructuralInterface.h"

StructuralInterface::StructuralInterface (StructuralEntity *parent)
    : StructuralEntity (parent)
{
  setCategory (Structural::Interface);
  setType (Structural::NoType);

  setResizable (false);

  setTop (0);
  setLeft (0);
  setWidth (ST_DEFAULT_INTERFACE_W);
  setHeight (ST_DEFAULT_INTERFACE_H);

  if (!ST_DEFAULT_WITH_INTERFACES)
  {
    setHidden (true);
  }
}

StructuralInterface::~StructuralInterface () {}

void
StructuralInterface::adjust (bool collision, bool recursion)
{
  StructuralEntity::adjust (collision, recursion);

  // Adjusting position...
  StructuralEntity *parent = getParent ();

  if (parent != NULL || !ST_DEFAULT_WITH_BODY)
  {
    if (!collision)
    {
      // Tries (10x) to find a position where there is no collision
      // with others relatives
      for (int i = 0; i < 10; i++)
      {
        bool colliding = false;

        foreach (StructuralEntity *entity, StructuralUtil::getNeighbors (this))
        {
          if (this != entity)
          {
            int max = 1000;
            int n = 0;

            qreal current = 0.0;

            entity->setSelectable (false);

            while (collidesWithItem (entity, Qt::IntersectsItemBoundingRect))
            {
              QLineF line = QLineF (
                  getLeft () + getWidth () / 2, getTop () + getHeight () / 2,
                  entity->getWidth () / 2, entity->getHeight () / 2);

              line.setAngle (qrand () % 360);

              current += (double)(qrand () % 100) / 1000.0;

              setTop (getTop () + line.pointAt (current / 2).y ()
                      - line.p1 ().y ());
              setLeft (getLeft () + line.pointAt (current / 2).x ()
                       - line.p1 ().x ());

              if (++n > max)
                break;
            }

            constrain ();

            entity->setSelectable (true);
          }
        }

        foreach (StructuralEntity *entity, StructuralUtil::getNeighbors (this))
          if (collidesWithItem (entity, Qt::IntersectsItemBoundingRect))
            colliding = true;

        if (!colliding)
          break;
      }
    }

    constrain ();

    StructuralUtil::adjustEdges (this);
  }
}

void
StructuralInterface::constrain ()
{
  StructuralEntity *parent = getParent ();

  if (parent != NULL)
  {
    QPointF tail (parent->getWidth () / 2, parent->getHeight () / 2);
    QPointF head (getLeft () + getWidth () / 2, getTop () + getHeight () / 2);

    if (tail == head)
    {
      head.setX (tail.x ());
      head.setY (tail.y () - 10);
    }

    QPointF p = head;
    QLineF line (tail, head);
    bool status = true;

    qreal current = 1.0;
    qreal step = 0.01;

    if (!parent->contains (p))
    {
      step = -0.01;
      status = false;
    }

    do
    {
      current += step;
      p = line.pointAt (current);
    } while (parent->contains (p) == status);

    if (QLineF (p, head).length () > 7)
    {
      setTop (p.y () - getHeight () / 2);
      setLeft (p.x () - getWidth () / 2);
    }
  }
}

void
StructuralInterface::draw (QPainter *painter)
{
  int x = ST_DEFAULT_ENTITY_PADDING + ST_DEFAULT_INTERFACE_PADDING;
  int y = ST_DEFAULT_ENTITY_PADDING + ST_DEFAULT_INTERFACE_PADDING;
  int w = getWidth () - 2 * ST_DEFAULT_INTERFACE_PADDING;
  int h = getHeight () - 2 * ST_DEFAULT_INTERFACE_PADDING;

  painter->drawPixmap (
      x, y, w, h, QPixmap (StructuralUtil::getIcon (getType ())));

  if (!ST_DEFAULT_WITH_BODY && !ST_DEFAULT_WITH_FLOATING_INTERFACES)
  {
    if (getProperty (ST_ATTR_ENT_AUTOSTART)
        == ST_VALUE_TRUE)
    {
      painter->setPen (QPen (QBrush (QColor (76, 76, 76)), 2));
      painter->drawRect (x, y, w, h);
    }
  }

  if (!getError ().isEmpty () || !getWarning ().isEmpty ())
  {

    QString icon;

    if (!getError ().isEmpty ())
    {
      icon = QString (ST_DEFAULT_ALERT_ERROR_ICON);
    }
    else
    {
      icon = QString (ST_DEFAULT_ALERT_WARNING_ICON);
    }

    painter->drawPixmap (x + w / 2 - (ST_DEFAULT_ALERT_ICON_W - 3) / 2,
                         y + h / 2 - (ST_DEFAULT_ALERT_ICON_H - 3) / 2,
                         ST_DEFAULT_ALERT_ICON_W - 3,
                         ST_DEFAULT_ALERT_ICON_H - 3, QPixmap (icon));
  }

  if (isMoving ())
  {
    painter->setBrush (QBrush (Qt::NoBrush));
    painter->setPen (QPen (QBrush (Qt::black), 0));

    int moveX = x + getMoveLeft () - getLeft ();
    int moveY = y + getMoveTop () - getTop ();
    int moveW = w;
    int moveH = h;

    painter->drawRect (moveX, moveY, moveW, moveH);
  }
}
