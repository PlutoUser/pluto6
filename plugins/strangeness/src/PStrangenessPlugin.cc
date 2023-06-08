/////////////////////////////////////////////////////////////////////
//Plugin to add the strangeness particles Lambda(1405) and Sigma(1385)
//
//Pids are 70-73
//
//This plugin is automatically enabled. If you don't like it, call
//makeDistributionManager()->Disable("strangeness");
//in the very beginning of your macro
//
//////////////////////////////////////////////////////////////////////

#include "PStrangenessPlugin.h"

#include "PDistributionManager.h"
#include "PResonanceDalitz.h"


Bool_t PStrangenessPlugin::hyperon_hadron_decays{kTRUE};
Bool_t PStrangenessPlugin::hyperon_photon_decays{kTRUE};
Bool_t PStrangenessPlugin::hyperon_dalitz_decays{kTRUE};
Bool_t PStrangenessPlugin::hyperon_experimental_decays{kFALSE};

PStrangenessPlugin::PStrangenessPlugin(const Char_t *id, const Char_t *de): PDistributionCollection(id, de),
    is_initialized(0) {
    //    RequiresPlugin("elementary");
}

Bool_t PStrangenessPlugin::Activate(void) {
    return kTRUE;
}

PStrangenessPlugin::~PStrangenessPlugin() {
}


Bool_t PStrangenessPlugin::ExecCommand(const char *command, Double_t) {

    if (strcmp (command,"init") == 0) {
        if (!is_initialized) {
            is_initialized = 1;

            fprintf(stderr, "Strangeness plugin - flags status:\n"
                   "- Hadron:       %d\n"
                   "- Photon:       %d\n"
                   "- Dalitz:       %d\n"
                   "- Experimental: %d\n",
                   hyperon_hadron_decays, hyperon_photon_decays, hyperon_dalitz_decays, hyperon_experimental_decays);

            Double_t *system_alloc_verbosity = makeStaticData()->GetBatchValue("_system_alloc_verbosity");
            Double_t old = (*system_alloc_verbosity);
            (*system_alloc_verbosity) = 0;

            if (makeStaticData()->AddParticle(70, "Lambda1405", 1.406) > 0) {
                makeStaticData()->AddAlias("Lambda1405", "Lambda(1405)");

                makeStaticData()->SetParticleTotalWidth("Lambda1405", 0.05);
                makeStaticData()->SetParticleBaryon("Lambda1405", 1);
                makeStaticData()->SetParticleSpin("Lambda1405", 1);
                makeStaticData()->SetParticleParity("Lambda1405", -1);

                if (hyperon_hadron_decays) {
                    makeStaticData()->AddDecay("Lambda(1405) --> Sigma+ + pi-",   "Lambda1405", "Sigma+,pi-", 1. / 3);
                    makeStaticData()->AddDecay("Lambda(1405) --> Sigma- + pi+",   "Lambda1405", "Sigma-,pi+", 1. / 3);
                    makeStaticData()->AddDecay("Lambda(1405) --> Sigma0 + pi0",   "Lambda1405", "Sigma0,pi0", 1. / 3);
                }

                if (hyperon_photon_decays) {
                    makeStaticData()->AddDecay("Lambda(1405) --> Lambda + gamma", "Lambda1405", "Lambda,g",   0.0085);
                }

                if (hyperon_dalitz_decays) {
                    makeStaticData()->AddDecay("Lambda(1405) --> Lambda + dilepton", "Lambda1405", "Lambda,dilepton", 0.0085 / 137.);

                    PResonanceDalitz * dalitz = new PResonanceDalitz("Lambda1405_dalitz@Lambda1405_to_Lambda_dilepton", "dgdm from Zetenyi/Wolf", -1);
                    dalitz->setGm(0.719);
                    makeDistributionManager()->Add(dalitz);
                }
            } else {
                Error("ExecCommand", "PIDs blocked, plugin disabled");
            }


            if (makeStaticData()->AddParticle(-1, "Sigma1385+", 1.3828) > 0) {
                makeStaticData()->AddAlias("Sigma1385+", "Sigma(1385)+");

                makeStaticData()->SetParticleTotalWidth("Sigma1385+", 0.0358);
                makeStaticData()->SetParticleBaryon("Sigma1385+", 1);
                makeStaticData()->SetParticleLMass("Sigma1385+", 1.2);

                if (hyperon_hadron_decays) {
                    makeStaticData()->AddDecay("Sigma(1385)+ --> Lambda + pi+", "Sigma1385+", "Lambda,pi+", 0.8815);
                    makeStaticData()->AddDecay("Sigma(1385)+ --> Sigma+ + pi0", "Sigma1385+", "Sigma+,pi0", 0.05925);
                    makeStaticData()->AddDecay("Sigma(1385)+ --> Sigma0 + pi+", "Sigma1385+", "Sigma0,pi+", 0.05925);
                }
            } else {
                Error("ExecCommand", "PIDs blocked, plugin disabled");
            }


            if (makeStaticData()->AddParticle(-1, "Sigma1385-", 1.3872) > 0) {
                makeStaticData()->AddAlias("Sigma1385-", "Sigma(1385)-");

                makeStaticData()->SetParticleTotalWidth("Sigma1385-", 0.0394);
                makeStaticData()->SetParticleBaryon("Sigma1385-", 1);
                makeStaticData()->SetParticleLMass("Sigma1385-", 1.2);

                if (hyperon_hadron_decays) {
                    makeStaticData()->AddDecay("Sigma(1385)- --> Lambda + pi-", "Sigma1385-", "Lambda,pi-", 0.8815 );
                    makeStaticData()->AddDecay("Sigma(1385)- --> Sigma- + pi0", "Sigma1385-", "Sigma-,pi0", 0.05925);
                    makeStaticData()->AddDecay("Sigma(1385)- --> Sigma0 + pi-", "Sigma1385-", "Sigma0,pi-", 0.05925);
                }
            } else {
                Error("ExecCommand", "PIDs blocked, plugin disabled");
            }


            if (makeStaticData()->AddParticle(-1, "Sigma13850", 1.3837) > 0) {
                makeStaticData()->AddAlias("Sigma13850", "Sigma(1385)0");

                makeStaticData()->SetParticleTotalWidth("Sigma13850", 0.0365);
                makeStaticData()->SetParticleBaryon("Sigma13850", 1);
                makeStaticData()->SetParticleLMass("Sigma13850", 1.2);
                makeStaticData()->SetParticleSpin("Sigma13850", 3);
                makeStaticData()->SetParticleParity("Sigma13850", 1);

                if (hyperon_hadron_decays) {
                    makeStaticData()->AddDecay("Sigma(1385)0 --> Lambda + pi0",   "Sigma13850", "Lambda,pi0", 0.87000);
                    makeStaticData()->AddDecay("Sigma(1385)0 --> Lambda + g",     "Sigma13850", "Lambda,g",   0.01300 * (1. - 1./137.));
                    makeStaticData()->AddDecay("Sigma(1385)0 --> Sigma+ + pi-",   "Sigma13850", "Sigma+,pi-", 0.117 / 3);
                    makeStaticData()->AddDecay("Sigma(1385)0 --> Sigma- + pi+",   "Sigma13850", "Sigma-,pi+", 0.117 / 3);
                    makeStaticData()->AddDecay("Sigma(1385)0 --> Sigma0 + pi0",   "Sigma13850", "Sigma0,pi0", 0.117 / 3);
                }

                if (hyperon_dalitz_decays) {
                    makeStaticData()->AddDecay("Sigma(1385)0 --> Lambda + dilepton", "Sigma13850", "Lambda,dilepton", 0.013 / 137.);
                    PResonanceDalitz * dalitz = new PResonanceDalitz("Sigma13850_dalitz@Sigma13850_to_Lambda_dilepton", "dgdm from Zetenyi/Wolf", -1);
                    dalitz->setGm(0.719);
                    makeDistributionManager()->Add(dalitz);
                }
            } else {
                Error("ExecCommand", "PIDs blocked, plugin disabled");
            }


            if (makeStaticData()->AddParticle(-1,"Lambda1520", 1.5195) > 0) {
                makeStaticData()->AddAlias("Lambda1520","Lambda(1520)");

                makeStaticData()->SetParticleTotalWidth("Lambda1520", 0.0156);
                makeStaticData()->SetParticleBaryon("Lambda1520", 1);
                makeStaticData()->SetParticleSpin("Lambda1520", 3);
                makeStaticData()->SetParticleParity("Lambda1520", 1);

                if (hyperon_hadron_decays) {
                    makeStaticData()->AddDecay("Lambda(1520) --> Lambda + pi0 + pi0", "Lambda1520", "Lambda,pi0,pi0", 0.2 / 3); // -
                    makeStaticData()->AddDecay("Lambda(1520) --> Lambda + pi+ + pi-", "Lambda1520", "Lambda,pi+,pi-", 0.1 / 3); // old BR .014638
                }

                if (hyperon_photon_decays) {
                    makeStaticData()->AddDecay("Lambda(1520) --> Lambda + g",         "Lambda1520", "Lambda,g",       0.0085);
                }

                if (hyperon_experimental_decays) {
                    makeStaticData()->AddDecay("Lambda(1520) --> Sigma0 + pi0",       "Lambda1520", "Sigma0,pi0",     0.139096); // -
                    makeStaticData()->AddDecay("Lambda(1520) --> Sigma+ + pi-",       "Lambda1520", "Sigma+,pi-",     0.139096); // -
                    makeStaticData()->AddDecay("Lambda(1520) --> Sigma- + pi+",       "Lambda1520", "Sigma-,pi+",     0.139096); // -
                    makeStaticData()->AddDecay("Lambda(1520) --> Sigma0 + pi0 + pi0", "Lambda1520", "Sigma0,pi0,pi0", 0.009/5.0); // -
                    makeStaticData()->AddDecay("Lambda(1520) --> Sigma0 + pi+ + pi-", "Lambda1520", "Sigma0,pi+,pi-", 0.009/5.0); // -
                }

                if (hyperon_dalitz_decays) {
                    makeStaticData()->AddDecay("Lambda(1520) --> Lambda + dilepton",  "Lambda1520", "Lambda,dilepton", .007948/137.);

                    PResonanceDalitz * dalitz = new PResonanceDalitz("Lambda1520_dalitz@Lambda1520_to_Lambda_dilepton", "dgdm from Zetenyi/Wolf", -1);
                    dalitz->setGm(0.719);
                    makeDistributionManager()->Add(dalitz);
                }
            } else {
                Error("ExecCommand", "PIDs blocked, plugin disabled");
            }


            if (makeStaticData()->AddParticle(75,"Xi1530-", 1.5352) > 0) {
                makeStaticData()->AddAlias("Xi1530-","Xi(1530)-");

                makeStaticData()->SetParticleTotalWidth("Xi1530-", 0.091);
                makeStaticData()->SetParticleBaryon("Xi1530-", 1);
                makeStaticData()->SetParticleSpin("Xi1530-", 2);
                makeStaticData()->SetParticleParity("Xi1530-", 1);

                if (hyperon_hadron_decays) {
                    makeStaticData()->AddDecay("Xi(1530)- --> Xi0 + pi-", "Xi1530-", "Xi0,pi-", 1. / 2.0);
                    makeStaticData()->AddDecay("Xi(1530)- --> Xi- + pi0", "Xi1530-", "Xi-,pi0", 1. / 2.0);
                }

                if (hyperon_photon_decays) {
                    makeStaticData()->AddDecay("Xi(1530)- --> Xi- + g",   "Xi1530-", "Xi-,g",   .037);
                }

                if (hyperon_dalitz_decays) {
                    makeStaticData()->AddDecay("Xi(1530)- --> Xi- + dilepton",  "Xi1530-", "Xi-,dilepton", .037/137.);

                    PResonanceDalitz * dalitz = new PResonanceDalitz("Xi1530-_dalitz@Xi1530-_to_Xi-_dilepton", "dgdm from Zetenyi/Wolf", -1);
                    dalitz->setGm(0.719);
                    makeDistributionManager()->Add(dalitz);
                }
            } else {
                Error("ExecCommand", "PIDs blocked, plugin disabled");
            }


            if (makeStaticData()->AddParticle(76,"Xi15300", 1.53178) > 0) {
                makeStaticData()->AddAlias("Xi15300","Xi(1530)0");

                makeStaticData()->SetParticleTotalWidth("Xi15300", 0.099);
                makeStaticData()->SetParticleBaryon("Xi15300", 1);
                makeStaticData()->SetParticleSpin("Xi15300", 2);
                makeStaticData()->SetParticleParity("Xi15300", 1);

                if (hyperon_hadron_decays) {
                    makeStaticData()->AddDecay("Xi(1530)0 --> Xi0 + pi0", "Xi15300", "Xi0,pi0", 1. / 2.0);
                    makeStaticData()->AddDecay("Xi(1530)0 --> Xi- + pi+", "Xi15300", "Xi-,pi+", 1. / 2.0);
                }

                if (hyperon_photon_decays) {
                    makeStaticData()->AddDecay("Xi(1530)0 --> Xi0 + g",   "Xi15300", "Xi0,g",   .037);
                }

                if (hyperon_dalitz_decays) {
                    makeStaticData()->AddDecay("Xi(1530)0 --> Xi0 + dilepton",  "Xi15300", "Xi0,dilepton", .037/137.);

                    PResonanceDalitz * dalitz = new PResonanceDalitz("Xi15300_dalitz@Xi15300_to_Xi0_dilepton", "dgdm from Zetenyi/Wolf", -1);
                    dalitz->setGm(0.719);
                    makeDistributionManager()->Add(dalitz);
                }
            } else {
                Error("ExecCommand", "PIDs blocked, plugin disabled");
            }


            if (makeStaticData()->AddParticle(79, "Delta2050++", 2.05) > 0) {
                makeStaticData()->AddAlias("Delta2050++", "Delta(2050)++");

                makeStaticData()->SetParticleTotalWidth("Delta2050++", 0.25);
                makeStaticData()->SetParticleBaryon("Delta2050++", 1);

                if (hyperon_hadron_decays) {
                    makeStaticData()->AddDecay("Delta(2050)++ --> Sigma(1385)+ + K+", "Delta2050++", "Sigma1385+,K+", 1.0);
                }
            } else {
                Error("ExecCommand", "PIDs blocked, plugin disabled");
            }

            (*system_alloc_verbosity) = old;
        }
        return kTRUE;
    }

    return kFALSE;
}


ClassImp(PStrangenessPlugin)

