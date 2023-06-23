// Author: I. Froehlich
// Written:22.1.2018
// Revised:

#ifndef _PTGENPHASESPACE_H_
#define _PTGENPHASESPACE_H_


#include "PChannelModel.h"
#include "PGenBod.h"
#include "TGenPhaseSpace.h"

class PTGenPhaseSpace : public PChannelModel  {

 public:
    PTGenPhaseSpace();
    PTGenPhaseSpace(const Char_t *id, const Char_t *de, Int_t key);

    PDistribution *Clone(const char*delme=NULL) const;

    Bool_t Init(void);
    Bool_t SampleMomentum(void);

    using PChannelModel::GetWeight;
    Double_t GetWeight();

    void   Print(const Option_t* delme=NULL) const;  //Debug info

 private:

    TGenPhaseSpace *event;
    PParticle *parent, *daughter[MAX_GENBOD_NUM];
    int n_daughters;

    ClassDef(PTGenPhaseSpace, 0) //Wrapper to ROOT TGenPhaseSpace
};

#endif


