/////////////////////////////////////////////////////////////////////
//Plugin to add some exotic particles
//see doc/particle_list.txt
//
//
//This plugin is automatically enabled. If you don't like it, call
//makeDistributionManager()->Disable("exotics");
//in the very beginning of your macro
//
//////////////////////////////////////////////////////////////////////

#include "PExoticsPlugin.h"

#include "PDistributionManager.h"
#include "PResonanceDalitz.h"

PExoticsPlugin::PExoticsPlugin(const Char_t *id, const Char_t *de) :
    PDistributionCollection(id, de), is_initialized(0) {
    //    RequiresPlugin("elementary");
}

Bool_t PExoticsPlugin::Activate(void) {
    return kTRUE;
}

PExoticsPlugin::~PExoticsPlugin() {
}


Bool_t PExoticsPlugin::ExecCommand(const char *command, Double_t) {

    if (strcmp (command,"init") == 0) {
        if (!is_initialized) {
            is_initialized = 1;

            Double_t *system_alloc_verbosity = makeStaticData()->GetBatchValue("_system_alloc_verbosity");
            Double_t old = (*system_alloc_verbosity);
            (*system_alloc_verbosity) = 0;

	    //f0(980)
	    if (makeStaticData()->AddParticle(200, "f0_980", 0.99) > 0) {
		makeStaticData()->AddAlias("f0_980", "f0(980)");
		makeStaticData()->SetParticleCharge("f0_980", 0);
		makeStaticData()->SetParticleTotalWidth("f0_980", 0.05);
		makeStaticData()->SetParticleMeson("f0_980", kTRUE);
		makeStaticData()->AddDecay("f_0(980) --> pi+ + pi-", "f0_980", "pi+,pi-", 2.0/3.0);
		makeStaticData()->AddDecay("f_0(980) --> pi0 + pi0", "f0_980", "pi0,pi0", 1.0/3.0);
	    } else {
		Error("ExecCommand", "PID blocked for f0_980, plugin disabled");
		(*system_alloc_verbosity) = old;
		return kFALSE;
            }

	    // --------------------------------------------------------------------
	    // PIDs 201-203: a0(980) Isospin-1 Multiplet (Flatté candidates)
	    // Note: KK-bar channels are omitted here intentionally. They will be 
	    // handled later via Flatté parameterization to avoid static
	    // phase-space threshold violations.
	    // --------------------------------------------------------------------
	    // BEGINN AI generated (Gemini)
	    
	    // PID 201: Neutral a0(980)
	    if (makeStaticData()->AddParticle(201, "a0_980_0", 0.980) > 0) {
		makeStaticData()->AddAlias("a0_980_0", "a_0(980)0");
		makeStaticData()->SetParticleTotalWidth("a0_980_0", 0.075); // PDG effective width
		makeStaticData()->SetParticleBaryon("a0_980_0", 0);
		makeStaticData()->SetParticleMeson("a0_980_0", 1);
		makeStaticData()->SetParticleSpin("a0_980_0", 0);
		makeStaticData()->SetParticleParity("a0_980_0", 1);
		
		// Dominant hadronic decay
		makeStaticData()->AddDecay("a_0(980)0 --> pi0 + eta", "a0_980_0", "pi0,eta", 1.0);
	    } else {
		Error("ExecCommand", "PID 201 blocked! PExoticsPlugin disabled.");
		(*system_alloc_verbosity) = old;
		return kFALSE;
	    }

	    // PID 202: Positive a0(980)
	    if (makeStaticData()->AddParticle(202, "a0_980+", 0.980) > 0) {
		makeStaticData()->AddAlias("a0_980+", "a_0(980)+");
		makeStaticData()->SetParticleTotalWidth("a0_980+", 0.075);
		makeStaticData()->SetParticleBaryon("a0_980+", 0);
		makeStaticData()->SetParticleMeson("a0_980+", 1);
		makeStaticData()->SetParticleSpin("a0_980+", 0);
		makeStaticData()->SetParticleParity("a0_980+", 1);
		
		// Dominant hadronic decay
		makeStaticData()->AddDecay("a_0(980)+ --> pi+ + eta", "a0_980+", "pi+,eta", 1.0);
	    } else {
		Error("ExecCommand", "PID 202 blocked! PExoticsPlugin disabled.");
		(*system_alloc_verbosity) = old;
		return kFALSE;
	    }
	    
	    // PID 203: Negative a0(980)
	    if (makeStaticData()->AddParticle(203, "a0_980-", 0.980) > 0) {
		makeStaticData()->AddAlias("a0_980-", "a_0(980)-");
		makeStaticData()->SetParticleTotalWidth("a0_980-", 0.075);
		makeStaticData()->SetParticleBaryon("a0_980-", 0);
		makeStaticData()->SetParticleMeson("a0_980-", 1);
		makeStaticData()->SetParticleSpin("a0_980-", 0);
		makeStaticData()->SetParticleParity("a0_980-", 1);
		
		// Dominant hadronic decay
		makeStaticData()->AddDecay("a_0(980)- --> pi- + eta", "a0_980-", "pi-,eta", 1.0);
	    } else {
		Error("ExecCommand", "PID 203 blocked! PExoticsPlugin disabled.");
		(*system_alloc_verbosity) = old;
		return kFALSE;
	    }
	    //END AI generated

	    // PID 204: phi(2170) (PDG average mass and width, July 2026)
	    if (makeStaticData()->AddParticle(204, "phi2170", 2.164) > 0) {
		makeStaticData()->AddAlias("phi2170", "phi(2170)");
		makeStaticData()->SetParticleCharge("phi2170", 0);
		makeStaticData()->SetParticleTotalWidth("phi2170", 0.088);
		makeStaticData()->SetParticleMeson("phi2170", kTRUE);
		// Default decay channels: the branching fractions below are placeholders and may be modified by users depending on their intended study.
		makeStaticData()->AddDecay("phi2170_to_phi_pipi", "phi2170", "phi,pi+,pi-",   1.0/3.0);
		makeStaticData()->AddDecay("phi2170_to_KKpipi",   "phi2170", "K+,K-,pi+,pi-", 1.0/3.0);
		makeStaticData()->AddDecay("phi2170_to_phif0",    "phi2170", "phi,f0_980",    1.0/3.0);

	    } else {
                Error("ExecCommand", "PID blocked for phi2170, plugin disabled");
		(*system_alloc_verbosity) = old;
                return kFALSE;
            }

            (*system_alloc_verbosity) = old;
        }
        return kTRUE;
    }

    return kFALSE;
}


ClassImp(PExoticsPlugin)

