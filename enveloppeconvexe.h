#ifndef ENVELOPPECONVEXE_H
#define ENVELOPPECONVEXE_H

#include <QObject>
#include <vector>
#include <complex>
#include <map>

using namespace std;

  class EnveloppeConvexe : public QObject
  {    Q_OBJECT

  private:
    typedef map<double, complex<double> > MapDoubleComplex;
    typedef map<double, complex<double> >::iterator ItMap;
    typedef vector< complex<double> > EnsembleDePoints;
    typedef EnsembleDePoints::iterator IteratorEnsembleDePoints;

    double AnglePositif(complex<double>, complex<double>);
    MapDoubleComplex computeTableauPondere1(complex<double>,complex<double>);
    MapDoubleComplex computeTableauPondere(complex<double>,complex<double>);

  public:
    explicit EnveloppeConvexe(QObject *parent = 0);
    ~EnveloppeConvexe();

    EnsembleDePoints* monEnsembleDePoints;
    EnsembleDePoints Enveloppe;
    EnsembleDePoints Interieur;
    EnsembleDePoints *pEnveloppe;
    EnsembleDePoints *pInterieur;

    void initEnveloppeConvexe(vector< complex<double> >*);
    void compute();	// avec mini de arg(vecteur - vecteur)
    string toString( EnsembleDePoints);

  signals:
       void SIGNAL_Evc(vector< complex<double> > *,vector< complex<double> > *);
  public slots:
       void SLOT_computeEvc(vector< complex<double> > *);
    };

#endif // ENVELOPPECONVEXE_H
