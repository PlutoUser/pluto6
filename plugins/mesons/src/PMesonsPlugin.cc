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

Bool_t PMesonsPlugin::experimental_decays{kFALSE};

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

                if (experimental_decays) {
                    makeStaticData()->AddDecay("X17 --> e+ + e-",           "X17", "e+,e-",         1);
                    makeStaticData()->AddDecay("eta --> pi+ + pi- + X17",   "eta", "pi+,pi-,X17",   0.001);
                }
            } else {
                Error("ExecCommand", "PIDs blocked, plugin disabled");
            }


            if (makeStaticData()->AddParticle(-1,"f1", 1.2821) > 0) {
                makeStaticData()->AddAlias("f1","f1(1285)");
                makeStaticData()->SetParticleTotalWidth("f1", 0.0242);
                makeStaticData()->SetParticleMeson("f1", 1);
                makeStaticData()->SetParticleSpin("f1", 1);
                makeStaticData()->SetParticleParity("f1", 1);
                makeStaticData()->SetParticleCharge("f1", 0);
                makeStaticData()->SetParticleIsospin("f1", 0);

                makeStaticData()->AddDecay("f1 --> pi+ + pi0 + eta",    "f1", "pi+,pi-,eta",        0.35);
                makeStaticData()->AddDecay("f1 --> 2pi0 + pi+ + pi-",   "f1", "pi+,pi-,pi0,pi0",    0.218);
                makeStaticData()->AddDecay("f1 --> 2pi+ + 2pi-",        "f1", "pi+,pi-,pi+,pi-",    0.109);
            }

            (*system_alloc_verbosity) = old;
        }
        return kTRUE;
    }

    return kFALSE;
}


ClassImp(PMesonsPlugin)
