#include <iostream>     // pour debugging
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "coloredqpoint.h"
#include <QDateTime>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  monAfficheur   = new Afficheur;
  Evc            = new EnveloppeConvexe;
  ensemblePoints = new vectorComplex ;
  enveloppe      = new vectorComplex;
  interieur      = new vectorComplex;
  //ensColoredPoints      = new vector<ColoredQPoint *>;

  //this->setFixedSize(400, 600);

  QPushButton *quit = new QPushButton("Quit");
  quit->setFont(QFont("Times", 18, QFont::Bold));

  QPushButton *run = new QPushButton("Run");
  run->setFont(QFont("Times", 18, QFont::Bold));
  run->move(110,00);

  QVBoxLayout *gridLayout =  new QVBoxLayout;
  gridLayout->addWidget(quit);
  gridLayout->addWidget(run);
  gridLayout->addWidget(monAfficheur);

  setLayout(gridLayout);

  connect(quit, SIGNAL(clicked()), qApp, SLOT(quit()));
  connect(run, SIGNAL(clicked()), this, SLOT(SLOT_run()));
  connect(this, SIGNAL(SIGNAL_computeEvc(vector< complex<double> > *)), Evc, SLOT(SLOT_computeEvc(vector< complex<double> > *)));
  connect(Evc, SIGNAL(SIGNAL_Evc(vector< complex<double> > *,vector< complex<double> > *)), this, SLOT(SLOT_evc(vector< complex<double> > *, vector< complex<double> > *)));
  connect(this, SIGNAL(SIGNAL_display(vector<ColoredQPoint *> *)), monAfficheur, SLOT(SLOT_display(vector<ColoredQPoint *> *)));
  connect(monAfficheur, SIGNAL(SIGNAL_displayEnded(int)), this, SLOT(SLOT_displayEnded(int)));

}

MainWindow::~MainWindow()
{
  delete ui;
}
void MainWindow::SLOT_run(void){

  int Nbre = 200;
  qsrand( QDateTime::currentDateTime().toTime_t() );
  ensemblePoints->clear();
  for(int i=0; i<100;i++)
    {
      complex<double> c(qrand() % (Nbre + 1),qrand() % (Nbre + 1));
      ensemblePoints->push_back(c);
    }

  emit SIGNAL_computeEvc(ensemblePoints);
  ensemblePoints->clear();;
}

void MainWindow::SLOT_evc(vector< complex<double> > *n, vector< complex<double> > *m){

  vector<ColoredQPoint *>  *ensColoredPoints = new vector<ColoredQPoint *>;

  vector< complex<double> >::iterator it ;
  for(it =m->begin(); it != m->end(); ++it) {
       complex<double> c = *it;
       QPoint point(c.real(), c.imag());
       ColoredQPoint *A = new ColoredQPoint();
       A->setQPoint(point);
       A->setQColor(QColor(0, 255, 0, 127));
       ensColoredPoints->push_back(A);
        cout<<"<!-- checkpoint 2 = "<<ensColoredPoints->capacity()<<endl;
   }

  vector< complex<double> >::iterator begin = n->begin()  ;
  vector< complex<double> >::iterator end = n->end()  ;
  while(begin != end) {
       complex<double> c = *begin;
       QPoint point(c.real(), c.imag());
       ColoredQPoint *A = new ColoredQPoint();
       A->setQPoint(point);
       A->setQColor(QColor(255, 0, 0, 127));
       ensColoredPoints->push_back(A);
       begin++;
       cout<<"<!-- checkpoint 1 = "<<ensColoredPoints->capacity()<<endl;
   }
  n->clear();
  m->clear();

  emit SIGNAL_display(ensColoredPoints);


}
void MainWindow::SLOT_displayEnded(int status){
  cout<<"<!-- le traitement s'est termine avec le statut = "<<status<<endl;
}


