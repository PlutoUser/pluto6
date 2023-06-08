// Author: I. Froehlich
// Written: 12.10.2008
// Revised:
// Updates: Rafał Lalik, 05.06.2023 - New Y* decays channels
//                                  - Software switches to modify decays
//


#ifndef _PSTRANGENESS_PLUGIN_H_
#define _PSTRANGENESS_PLUGIN_H_

#include "TROOT.h"

#include "PChannelModel.h"
#include "PDistributionManagerUtil.h"
#include "PDistributionCollection.h"

using namespace std;

class PStrangenessPlugin : public PDistributionCollection {

 public:

    //constructor
    PStrangenessPlugin(const Char_t *id, const Char_t *de);
    //destructor
    ~PStrangenessPlugin();

    Bool_t ExecCommand(const char *command, Double_t value);
    Bool_t Activate(void);

    static void EnableHadronDecays(Bool_t enabled) { hyperon_hadron_decays = enabled; }
    static void EnablePhotonDecays(Bool_t enabled) { hyperon_photon_decays = enabled; }
    static void EnableDalitzDecays(Bool_t enabled) { hyperon_dalitz_decays = enabled; }
    static void EnableExperimentalDecays(Bool_t enabled) { hyperon_experimental_decays = enabled; }
 private:

    Int_t is_initialized;

    static Bool_t hyperon_hadron_decays;
    static Bool_t hyperon_photon_decays;
    static Bool_t hyperon_dalitz_decays;
    static Bool_t hyperon_experimental_decays;

    ClassDef(PStrangenessPlugin, 0) //Plugin to add new particles with strangeness and their decays
};

#endif //_PSTRANGENESS_PLUGIN_H_







