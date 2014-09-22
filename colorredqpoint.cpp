#include "coloredqpoint.h"

ColoredQPoint::ColoredQPoint(QObject *parent) :
  QObject(parent)
{
  point.setX(0);
  point.setY(0);
  color = QColor(255, 0, 0, 127);
}
void ColoredQPoint::setColoredQPoint(QPoint p, QColor c)   {
  point.setX(p.x());
  point.setY(p.y());
  color = c;
}

void ColoredQPoint::setColoredQPoint(int x, int y, QColor c)   {
  point.setX(x);
  point.setY(y);
  color = c;
}

void ColoredQPoint::setQPoint(QPoint p)   {
  point.setX(p.x());
  point.setY(p.y());
}

void ColoredQPoint::setQColor(QColor c)   {
  color = c;
}

QColor ColoredQPoint::getColor()   {
  return color;
}

QPoint ColoredQPoint::getPoint()   {
  return point;
}
