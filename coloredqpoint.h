#ifndef COLOREDQPOINT_H
#define COLOREDQPOINT_H

#include <QObject>
#include <QPoint>
#include <QColor>

class ColoredQPoint : public QObject
{
  Q_OBJECT
public:
  explicit ColoredQPoint(QObject *parent = 0);
  QPoint point;
  QColor color;

  void setColoredQPoint(QPoint, QColor);
  void setColoredQPoint(int, int, QColor);
  void setQPoint(QPoint);
  void setQColor(QColor);

  QPoint getPoint();
  QColor getColor();

signals:

public slots:

};

#endif // COLOREDQPOINT_H
