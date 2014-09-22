#include "afficheur.h"
#include <limits>

using namespace std;

Afficheur::Afficheur(QWidget *parent) :
  QWidget(parent)
{
  mesPoints = new vector<ColoredQPoint *>;
  scale = 1.0;
}
void Afficheur::paintEvent(QPaintEvent * /* event */)
{
  QPainter painter(this);

  //recherche de l'enveloppe rectangulaire

  double Xmax = std::numeric_limits<int>::min();
  double Xmin = std::numeric_limits<int>::max();
  double Ymax = std::numeric_limits<int>::min();
  double Ymin = std::numeric_limits<int>::max();;

  vector<ColoredQPoint *>::iterator it ;
  for(it = mesPoints->begin(); it != mesPoints->end(); ++it) {
      ColoredQPoint *colPoint = new ColoredQPoint;
      colPoint = *it;
      QPoint point = colPoint->getPoint();
      if ( point.x() > Xmax ) Xmax =  point.x();
      if ( point.x() < Xmin ) Xmin =  point.x();
      if ( point.y() > Ymax ) Ymax =  point.y();
      if ( point.y() < Ymin ) Ymin =  point.y();
  }
  //calcul de l'origine du nuage de points
  double Xorigine = (Xmax + Xmin)/2.0;
  double Yorigine = (Ymax + Ymin)/2.0;

  //calcul du centre de la zone d'affichage
  double centreX = this->width() / 2.0;
  double centreY =  this->height() / 2.0;

 // calcul des facteurs d'échelle
  double Xscale = 0.9*this->width() / (Xmax - Xmin);
  double Yscale = 0.9*this->height() / (Ymax - Ymin);

  // dessin des points colorés

  for(it = mesPoints->begin(); it != mesPoints->end(); ++it) {
      ColoredQPoint *colPoint = new ColoredQPoint;
      colPoint = *it;
      QPoint point = colPoint->getPoint();
      painter.setBrush(colPoint->getColor());
      painter.drawEllipse(centreX - Xscale*(Xorigine -point.x()) , centreY - Yscale*(Yorigine -point.y()), 10, 10);
  }
}
void Afficheur::SLOT_display(vector<ColoredQPoint* > * v) {
  mesPoints = v;
  update();
  SIGNAL_displayEnded(0);
}
