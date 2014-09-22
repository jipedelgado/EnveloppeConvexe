#ifndef AFFICHEUR_H
#define AFFICHEUR_H

#include <iostream>     // for debugging
#include <QWidget>
#include <QPainter>
#include <vector>
#include "coloredqpoint.h"

using namespace std;
class Afficheur : public QWidget
{
  Q_OBJECT
public:
  vector<ColoredQPoint *> *mesPoints;
  double scale;
  explicit Afficheur(QWidget *parent = 0);

  void paintEvent(QPaintEvent * /* event */);

signals:
  void SIGNAL_displayEnded(int);

public slots:
  void SLOT_display(vector<ColoredQPoint *> *);
};

#endif // AFFICHEUR_H
