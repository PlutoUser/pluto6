// Author: I. Froehlich
// Written: 03.07.2026
// Revised:
// Updates: 
//


#ifndef _PEXOTICS_PLUGIN_H_
#define _PEXOTICS_PLUGIN_H_

#include "TROOT.h"

#include "PChannelModel.h"
#include "PDistributionManagerUtil.h"
#include "PDistributionCollection.h"

using namespace std;

class PExoticsPlugin : public PDistributionCollection {

 public:

    //constructor
    PExoticsPlugin(const Char_t *id, const Char_t *de);
    //destructor
    ~PExoticsPlugin();

    Bool_t ExecCommand(const char *command, Double_t value);
    Bool_t Activate(void);

 private:

    Int_t is_initialized;

    ClassDef(PExoticsPlugin, 0) //Plugin to add exotic particles 
};

#endif //_PEXOTICS_PLUGIN_H_







