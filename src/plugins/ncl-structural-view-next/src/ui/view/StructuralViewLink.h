#ifndef QNSTVIEWLINK_H
#define QNSTVIEWLINK_H

#define PI 3.14159265

#include <cmath>

#include "StructuralEntity.h"

class StructuralViewLink : public StructuralEntity
{
public:
    StructuralViewLink(StructuralEntity* parent = 0);
    virtual ~StructuralViewLink();

    QLineF getLine() const;

    void setLine(QLineF line);

    virtual void adjust(bool avoidCollision = false,  bool rec = true);

protected:
    virtual void draw(QPainter* painter);

    virtual void delineate(QPainterPath* painter) const;

    virtual void move(QGraphicsSceneMouseEvent* event);

    virtual void resize(QGraphicsSceneMouseEvent* event);

private:
    QLineF line;
};

#endif // QNSTVIEWLINK_H