/////////////////////////////////////////////////////////////////////
//Plugin to add the mesons particles Lambda(1405) and Sigma(1385)
//
//Pids are 70-73
//
//This plugin is automatically enabled. If you don't like it, call
//makeDistributionManager()->Disable("mesons");
//in the very beginning of your macro
//
//////////////////////////////////////////////////////////////////////

#include "PMesonsPlugin.h"

#include "PDistributionManager.h"
#include "PResonanceDalitz.h"

PMesonsPlugin::PMesonsPlugin(const Char_t *id, const Char_t *de):
    PDistributionCollection(id, de) {
    is_initialized = 0;
    //    RequiresPlugin("elementary");
}

Bool_t PMesonsPlugin::Activate(void) {
    return kTRUE;
}

PMesonsPlugin::~PMesonsPlugin() {
}


Bool_t PMesonsPlugin::ExecCommand(const char *command, Double_t) {

    if (strcmp (command,"init") == 0) {
        if (!is_initialized) {
            is_initialized = 1;

            Double_t *system_alloc_verbosity = makeStaticData()->GetBatchValue("_system_alloc_verbosity");
            Double_t old = (*system_alloc_verbosity);
            (*system_alloc_verbosity) = 0;

            if (makeStaticData()->AddParticle(117, "X17", 0.017) > 0) {
                // makeStaticData()->AddAlias("X17","x17");
                makeStaticData()->SetParticleTotalWidth("X17", 0.197/4e-14);
                makeStaticData()->SetParticleParity("X17", 1);
                makeStaticData()->AddDecay("X17 --> e+ e-",         "X17", "e+,e-", 1);
                makeStaticData()->AddDecay("eta --> pi+ pi- X17",   "eta", "pi+,pi-,X17", 0.001);
            } else {
                Error("ExecCommand", "PIDs blocked, plugin disabled");
            }

            (*system_alloc_verbosity) = old;
        }
        return kTRUE;
    }

    return kFALSE;
}


ClassImp(PMesonsPlugin)
