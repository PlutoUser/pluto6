// Author: R. Lalik
// Written: 12.06.2023
// Revised:
//

#ifndef _PMESONS_PLUGIN_H_
#define _PMESONS_PLUGIN_H_

#include "TROOT.h"

#include "PChannelModel.h"
#include "PDistributionManagerUtil.h"
#include "PDistributionCollection.h"

using namespace std;

class PMesonsPlugin : public PDistributionCollection {
public:
    PMesonsPlugin(const Char_t *id, const Char_t *de);
    ~PMesonsPlugin();

    Bool_t ExecCommand(const char *command, Double_t value);
    Bool_t Activate(void);

private:
    Int_t is_initialized;

    ClassDef(PMesonsPlugin, 0) //Plugin to add new particles with mesons and their decays
};

#endif //_PMESONS_PLUGIN_H_
