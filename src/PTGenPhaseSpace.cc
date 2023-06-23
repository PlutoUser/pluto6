/////////////////////////////////////////////////////////////////////
//
// Pluto wrapper to TGenPhaseSpace
//
/////////////////////////////////////////////////////////////////////


using namespace std;
#include <sstream>
#include <iostream>
#include <iomanip>

#include "PTGenPhaseSpace.h"


ClassImp(PTGenPhaseSpace)

PTGenPhaseSpace::PTGenPhaseSpace() {
    Fatal("PTGenPhaseSpace()", "Wrong constructor");
};

PTGenPhaseSpace::PTGenPhaseSpace(const Char_t *id, const Char_t *de, Int_t key) :
    PChannelModel (id, de, key) {

    parent  = NULL;
    n_daughters = 0;
    event = new TGenPhaseSpace();

    for (int i=0; i<MAX_GENBOD_NUM; i++) {
	daughter[i]=NULL;
    }
};

PDistribution *PTGenPhaseSpace::Clone(const char*) const {
    return new PTGenPhaseSpace((const PTGenPhaseSpace &)* this);
};

Bool_t PTGenPhaseSpace::Init(void) {
    parent = GetParticle("parent");
    if (!parent) {
	Warning("Init", "Parent not found");
	return kFALSE;
    }

    bool myloop=1;
    for (n_daughters=0; n_daughters<MAX_GENBOD_NUM && myloop; n_daughters++) {
	if (!daughter[n_daughters])
	    daughter[n_daughters] = GetParticle("daughter");
	if (!daughter[n_daughters]) {
	    myloop = 0;
	}
    }
    n_daughters--;

    return kTRUE;
};

Double_t PTGenPhaseSpace::GetWeight() {
    return 0;
}


Bool_t PTGenPhaseSpace::SampleMomentum(void) {

    int i;
    double em[n_daughters];

    for (i=0; i<n_daughters; i++) {
	em[i] = daughter[i]->M();
    }

    event->SetDecay(*parent, n_daughters, em);
    Double_t weight_max = event->GetWtMax();
    Int_t w_counter = 0;

 repeat2:

    Double_t w0 = event->Generate();

    if (w0/weight_max < PUtils::sampleFlat()) {
	if (w_counter < 10000) {
	    w_counter++;
	    goto repeat2; // take weight into account (R.H.)
	} else { // happens very rare (fixed bug Nr. 359)
	    return kFALSE;
	}
    }

    for (i=0; i<n_daughters; i++) {
	daughter[i]->SetVect4(*(event->GetDecay(i)));
	daughter[i]->Boost(-parent->BoostVector()); // go back to cm system
    }

    return kTRUE;
};

void PTGenPhaseSpace::Print(const Option_t*) const {
    BasePrint();
};


