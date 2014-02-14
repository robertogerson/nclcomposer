#include "Reference.h"

QnstReference::QnstReference(QnstEntity* parent)
  : QnstEdge(parent)
{
  setnstType(Qnst::Edge);
  setnstSubtype(Qnst::Reference);
}

QnstReference::~QnstReference()
{

}

void QnstReference::draw(QPainter* painter)
{
  if (getEntityA() != NULL && getEntityB() != NULL)
  {
    painter->setRenderHint(QPainter::Antialiasing, true);

    QLineF line = QLineF(QPointF(getEntityA()->getLeft() + getEntityA()->getWidth()/2,
                                 getEntityA()->getTop() + getEntityA()->getHeight()/2),
                         QPointF(getEntityB()->getLeft() + getEntityB()->getWidth()/2,
                                 getEntityB()->getTop() + getEntityB()->getHeight()/2));

    if (getEntityA()->getnstType() == Qnst::Interface)
    {
      line.setP1(getnstParent()->mapFromItem(getEntityA()->getnstParent(), line.p1()));
    }

    if (getEntityB()->getnstType() == Qnst::Interface)
    {
      line.setP2(getnstParent()->mapFromItem(getEntityB()->getnstParent(), line.p2()));
    }

    QPointF p1;

    QPointF pointa = line.p1();
    QPointF pointb = line.p2();

    if (pointa.x() <= pointb.x() && pointa.y() <= pointb.y())
    {
      painter->setPen(QPen(QBrush(QColor("#000000")), 1, Qt::DashLine));

      painter->drawLine(4+6,4+6, 4+6+getWidth()-12, 4+6+getHeight()-12);

      painter->setBrush(QBrush(QColor("#000000")));
      painter->setPen(Qt::NoPen);

      p1 = QPointF(4+6+getWidth()-12, 4+6+getHeight()-12);

    }
    else if (pointa.x() > pointb.x() && pointa.y() < pointb.y())
    {
      painter->setPen(QPen(QBrush(QColor("#000000")), 1, Qt::DashLine));

      painter->drawLine(4+6+getWidth()-12,4+6, 4+6, 4+6+getHeight()-12);

      painter->setBrush(QBrush(QColor("#000000")));
      painter->setPen(Qt::NoPen);

      p1 = QPointF(4+6, 4+6+getHeight()-12);

    }
    else if (pointa.x() < pointb.x() && pointa.y() > pointb.y())
    {
      painter->setPen(QPen(QBrush(QColor("#000000")), 1, Qt::DashLine));

      painter->drawLine(4+6, 4+6+getHeight()-12, 4+6+getWidth()-12, 4+6);

      painter->setBrush(QBrush(QColor("#000000")));
      painter->setPen(Qt::NoPen);

      p1 = QPointF(4+6+getWidth()-12, 4+6);

    }
    else if (pointa.x() > pointb.x() && pointa.y() > pointb.y())
    {
      painter->setPen(QPen(QBrush(QColor("#000000")), 1, Qt::DashLine));

      painter->drawLine(4+6+getWidth()-12, 4+6+getHeight()-12, 4+6, 4+6);

      painter->setBrush(QBrush(QColor("#000000")));
      painter->setPen(Qt::NoPen);

      p1 = QPointF(4+6, 4+6);
    }

    double angle = ::acos(line.dx() / line.length());

    if (line.dy() >= 0)
    {
      angle = (PI * 2) - angle;
    }

    QPointF p2 = p1 - QPointF(sin(angle + PI / 3) * 12, cos(angle + PI / 3) * 12);
    QPointF p3 = p1 - QPointF(sin(angle + PI - PI / 3) * 12, cos(angle + PI - PI / 3) * 12);

    QVector<QPointF> polygon;

    polygon.append(p1);
    polygon.append(p2);
    polygon.append(p3);

    painter->drawPolygon(QPolygonF(polygon));
  }
}

void QnstReference::delineate(QPainterPath* painter) const
{
  if (getEntityA() != NULL && getEntityB() != NULL)
  {
    QLineF line = QLineF(QPointF(getEntityA()->getLeft() + getEntityA()->getWidth()/2,
                                 getEntityA()->getTop() + getEntityA()->getHeight()/2),
                         QPointF(getEntityB()->getLeft() + getEntityB()->getWidth()/2,
                                 getEntityB()->getTop() + getEntityB()->getHeight()/2));

    if (getEntityA()->getnstType() == Qnst::Interface)
    {
      if(getnstParent())
        line.setP1(getnstParent()->mapFromItem(getEntityA()->getnstParent(), line.p1()));
    }

    if (getEntityB()->getnstType() == Qnst::Interface)
    {
      if(getnstParent())
        line.setP2(getnstParent()->mapFromItem(getEntityB()->getnstParent(), line.p2()));
    }

    QPointF p1;

    QPointF pointa = line.p1();
    QPointF pointb = line.p2();

    if (pointa.x() <= pointb.x() && pointa.y() <= pointb.y())
    {
      painter->addEllipse(4,4,3,3);

      p1 = QPointF(4+6+getWidth()-12, 4+6+getHeight()-12);

    }
    else if (pointa.x() > pointb.x() && pointa.y() < pointb.y())
    {
      painter->addEllipse(4+getWidth()-3,4,3,3);

      p1 = QPointF(4+6, 4+6+getHeight()-12);

    }
    else if (pointa.x() < pointb.x() && pointa.y() > pointb.y())
    {
      painter->addEllipse(4, 4+getHeight()-3, 3, 3);

      p1 = QPointF(4+6+getWidth()-12, 4+6);

    }
    else if (pointa.x() > pointb.x() && pointa.y() > pointb.y())
    {
      painter->addEllipse(4+getWidth()-3, 4+getHeight()-3, 3, 3);

      p1 = QPointF(4+6, 4+6);
    }

    double angle = ::acos(line.dx() / line.length());

    if (line.dy() >= 0)
    {
      angle = (PI * 2) - angle;
    }

    QPointF p2 = p1 - QPointF(sin(angle + PI / 3) * 12, cos(angle + PI / 3) * 12);
    QPointF p3 = p1 - QPointF(sin(angle + PI - PI / 3) * 12, cos(angle + PI - PI / 3) * 12);

    QVector<QPointF> polygon;

    polygon.append(p1);
    polygon.append(p2);
    polygon.append(p3);

    painter->addPolygon(QPolygonF(polygon));
  }
}