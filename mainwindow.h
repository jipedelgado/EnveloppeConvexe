#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/*
 *  2012/12/01 = Analyse et écriture algo de base
 *  2013/11/01 = Portage sur Qt
 *  2013/11/09 = finalisation du projet de base
 *
 *  Recherche de l'enveloppe convexe d'un nuage de points
 *  sur une suggestion de Gérard Berry dans un des cours du collège de France 2008
 *
 *  Les points sont générés de façon aléatoire
 *  l'enveloppe convexe et l'intérieur sont affichés selon 2 couleurs différentes
 *
 *  todo =
 *  2 - stockage et acquisition des points sur fichiers.
 *
 *
 **/

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

#include "afficheur.h"
#include "enveloppeconvexe.h"
#include "coloredqpoint.h"


namespace Ui {
  class MainWindow;
}

class MainWindow : public QWidget
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

  typedef vector< complex<double> > vectorComplex;

  Afficheur *monAfficheur;
  EnveloppeConvexe *Evc;
  vectorComplex *ensemblePoints;
  vectorComplex *enveloppe;
  vectorComplex *interieur;

  //vector<ColoredQPoint *> *ensColoredPoints;

private:
  Ui::MainWindow *ui;

signals:
  void SIGNAL_computeEvc(vector< complex<double> > *);
  void SIGNAL_display(vector<ColoredQPoint *> *);

public slots:
  void SLOT_run(void);
  void SLOT_evc(vector< complex<double> > *, vector< complex<double> > *);
  void SLOT_displayEnded(int);
};

#endif // MAINWINDOW_H
