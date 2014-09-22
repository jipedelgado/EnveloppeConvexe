#include <iostream>
#include <stdio.h>
#include <utility>
#include "enveloppeconvexe.h"
#include <limits>

EnveloppeConvexe::EnveloppeConvexe(QObject *parent) :
  QObject(parent)
{
  monEnsembleDePoints = new EnsembleDePoints;
  pEnveloppe = new EnsembleDePoints;
  pInterieur = new EnsembleDePoints;
}

void EnveloppeConvexe::initEnveloppeConvexe(vector< complex<double> >* v ){
    monEnsembleDePoints = v;
    Interieur = *v;
}
EnveloppeConvexe::~EnveloppeConvexe(){
    delete monEnsembleDePoints;
    delete pEnveloppe;
    delete pInterieur;
}
string EnveloppeConvexe::toString( EnsembleDePoints E){
    string aString;
    IteratorEnsembleDePoints begin = E.begin();
    IteratorEnsembleDePoints end =   E.end();
    stringstream sstr;
    while( begin != end){
        aString.append("( ");
        stringstream sstrReal;
        sstrReal << scientific << begin->real();
        aString.append(sstrReal.str());
        aString.append(" , ");
        stringstream sstrIm;
        sstrIm << scientific << begin->imag();
        aString.append(sstrIm.str());
        aString.append(" )\n");
        begin++;
    }
    return aString;
}
double EnveloppeConvexe::AnglePositif(complex<double> z1, complex<double> z2){
    // retourn l'angle entre le arguments  normalise entre 0 et 2Pi
        double deuxPI = 2*acos(-1);
        double result;
        double arg1 = arg(z1);
        if(arg1<0) arg1 += deuxPI;

	double arg2 = arg(z2);
	if(arg2<0) arg2 += deuxPI;

	result = arg2-arg1;
	if(result <0) return result + deuxPI;
	else return result;
}
EnveloppeConvexe::MapDoubleComplex EnveloppeConvexe::computeTableauPondere(
	complex<double> origine,complex<double> extremite)
{
	//double PI = acos(-1);
	//cout<<"PI = "<<PI<<endl<<endl;
	MapDoubleComplex T;
	IteratorEnsembleDePoints begin = monEnsembleDePoints->begin();
	IteratorEnsembleDePoints   end = monEnsembleDePoints->end();
	while(begin != end){
	    double tempo;
	    if(extremite != *begin && origine != *begin){
		// ci-git le coeur de l'algorihtme
		tempo = AnglePositif(extremite - origine, *begin - extremite);
		/* pour debug
		cout<<"origine = "<<origine<<"   extremite = "<<extremite<<
			"   vecteur = "<<extremite-origine<<
			"\ttempo = "<<tempo<<
			"   \t*begin = "<<*begin<<"   \tangle = "<<tempo<<endl;
		*/
		pair<double, complex<double> > aPairDoubleComplex;
		aPairDoubleComplex = make_pair (tempo,*begin);
		T.insert( aPairDoubleComplex);
	    }
	    begin++;
	}
    return T;
}
EnveloppeConvexe::MapDoubleComplex EnveloppeConvexe::computeTableauPondere1(
	complex<double> origine,complex<double> extremite)
{
	MapDoubleComplex T;
	IteratorEnsembleDePoints begin = monEnsembleDePoints->begin();
	IteratorEnsembleDePoints   end = monEnsembleDePoints->end();
	while(begin != end){
	    double tempo;
	    if(extremite != *begin && origine != *begin){
		// ci-git le coeur de l'algorihtme
		// tempo = ProduitScalaire(extremite - origine, *begin);
		tempo = arg(*begin - extremite + origine);
		/* pour debug
		cout<<"origine = "<<origine<<"   extremite = "<<extremite<<
			"   vecteur = "<<extremite-origine<<
			"   *begin = "<<*begin<<"    scalaire = "<<tempo<<endl;
		*/
		pair<double, complex<double> > aPairDoubleComplex;
		aPairDoubleComplex = make_pair (tempo,*begin);
		T.insert( aPairDoubleComplex);
	    }
	    begin++;
	}
    return T;
}
void EnveloppeConvexe::compute(){
        // pour protéger monEnsembleDePoints, mais pas indispensable
        cout<<"!-- entree de EnveloppeConvexe::compute()"<<endl;

        EnsembleDePoints* EnsPoints = monEnsembleDePoints;

	//recherche du point d'ordonnee minimum
	IteratorEnsembleDePoints   begin = EnsPoints->begin();
	IteratorEnsembleDePoints     end = EnsPoints->end();
	IteratorEnsembleDePoints courant = begin;
	double mini = numeric_limits<double>::max();
	while (begin != end){
	    if(begin->imag() < mini) {
		mini = begin->imag();
		courant = begin;
	    }
	    begin++;
	}
    // fin de recherche du point d'ordonnée minimum = *courant
     //   cout<< "courant mini = "<<*courant<<endl;
    // on retire ce point de Interieur
        IteratorEnsembleDePoints beginInterieur = Interieur.begin();
        IteratorEnsembleDePoints  endInterieur = Interieur.end();
        while (beginInterieur != endInterieur && *beginInterieur != *courant )
            beginInterieur++;
        Interieur.erase(beginInterieur);

// initialisation avant la boucle principale

	// premier argument de computeTableauPondere
	complex<double> origine(0,0);

	// deuxième argument de computeTableauPondere
	complex<double> extremite = *courant;

	// le premier élément de Enveloppe
	Enveloppe.push_back(extremite);

// boucle principale
	IteratorEnsembleDePoints first = EnsPoints->begin();
	IteratorEnsembleDePoints  last = EnsPoints->end();

	// on parcours EnsPoints
	while (first != last){
	//recherche du point d'angle minimum

	    // création du tableau (double, complex)
	    // ATTENTION = le premier élément d'une map doit être d'un
	    // type ordonnée. Donc pas complex !!
	    MapDoubleComplex Map = computeTableauPondere(origine, extremite);

	    // recherche dans Map du point d'angle minimum
	    ItMap begin = Map.begin();
	    ItMap  end  = Map.end();
	    ItMap courant = begin;
	    double min = 99999;// numeric_limits<double>::min();
	    while (begin != end){
		if(begin->first < min) {
		    min = begin->first;
		    courant = begin;
		}
		begin++;
	    }
	// fin de recherche dans Map du point d'angle minimum
	// cout<< "angle mini = "<<courant->first<<" point "<<courant->second<<endl<<endl;

	   // recherche dans monEnsembleDePoints du point d'angle minimum
	   IteratorEnsembleDePoints premier = EnsPoints->begin();
	   IteratorEnsembleDePoints  dernier = EnsPoints->end();
	   while(premier != dernier && *premier != courant->second)
	       premier++;
	   if(premier != dernier) {
		// on prépare l'appel à computeTableauPondere
		origine = extremite;
		extremite = *premier;

		// on recherche la présence de ce point dans Enveloppe
		IteratorEnsembleDePoints beginEnveloppe = Enveloppe.begin();
		IteratorEnsembleDePoints  endEnveloppe = Enveloppe.end();
		while (beginEnveloppe != endEnveloppe && *beginEnveloppe != extremite )
		    beginEnveloppe++;

		// si ce point n'est pas déjà dans Enveloppe, on l'ajoute à Enveloppe
		// et on le retire de Interieur
		if(beginEnveloppe == endEnveloppe){
			Enveloppe.push_back(extremite);
			// on le retire de Interieur
			IteratorEnsembleDePoints beginInterieur = Interieur.begin();
			IteratorEnsembleDePoints  endInterieur = Interieur.end();
			while (beginInterieur != endInterieur && *beginInterieur != extremite )
			    beginInterieur++;
			Interieur.erase(beginInterieur);
		}
	    }
	    first++;
	} // fin de la boucle principale
	//cout<<"Enveloppe = \n"<<toString(Enveloppe)<<endl<<endl;
	//cout<<"Interieur = \n"<<toString(Interieur)<<endl;
	//emit SIGNAL_Evc(Enveloppe,Interieur );
	cout<<"<!-- sortie de EnveloppeConvexe::compute()"<<endl;
}
void EnveloppeConvexe::SLOT_computeEvc(EnsembleDePoints* e){
  monEnsembleDePoints = e;
  Interieur = *e;
  compute();
  emit SIGNAL_Evc(&Enveloppe,&Interieur);
}

