////////////////////////////////////////////////////////
//  Small linear mesh to substitute the array from PData
//  The mesh is inherited from TF1, and allow to use
//  mesh->Draw()
//
//
//                    Author: I. Froehlich
//                    Written: 7.05.2007
//                    Revised:
//
////////////////////////////////////////////////////////


#include "PMesh.h"
#include <iostream>
#include "TH1.h"
#include "TROOT.h"
#include "TVirtualPad.h"

using namespace std;

PMesh::PMesh(Int_t psize, const Char_t *name) : TF1(name, "0", 0, 1) {
    // Copied from TF1 constructor...
    SetName(name);
    fNpar      = 0;

    fXmin      = 0.;
    fXmax      = 0.;

    fNpx       = psize-1;
#if ROOT_VERSION_CODE < ROOT_VERSION(6,12,0)
    fType      = 0;
#else
    fType      = EFType::kFormula;
#endif
    //    fFunction  = 0;
    fNdim = 1;

    if (psize <= 0) {
	Warning("PMesh", "Size %i not allowed", psize);
	td = NULL;
    }
    td   = new Double_t[psize];
    size = psize;
    max  = 0.;
    min = 0.;
}

PMesh::~PMesh() {
    if (td) delete[] td;
}

Double_t PMesh::EvalPar(const Double_t *x, const Double_t *) {
    return Eval(x[0]);
}

Double_t PMesh::Eval(Double_t x, Double_t, Double_t, Double_t) const {
    return GetLinearIP(x);
}

void PMesh::SetNode(Int_t node, Double_t v) {
    if ((node>=size) || (node<0))
	return;
    td[node] = v;
}

Double_t PMesh::GetNode(Int_t node) {
    if ((node>=size) || (node<0))
	return 0;
    return td[node];
}

void PMesh::Print(const Option_t*) const {
    cout << "Min:  " << min  << endl;
    cout << "Max:  " << max  << endl;
    cout << "Size: " << size << endl;
    TF1::Print();
}

Double_t PMesh::GetLinearIP(Double_t m) const {
    if ((m > min) && (m < max)) {

	Double_t dm = (max-min)/(size-1.);
	int bin     = int((m-min)/dm);

	double mlow = min + bin*dm,
	    mup  = mlow + dm,
	    wlow = td[bin],
	    wup  = td[bin+1];
	return ((mup*wlow-mlow*wup) + m*(wup-wlow))/dm;
    }
    //catch NAN
    return 0;     // mass out of bounds
}
