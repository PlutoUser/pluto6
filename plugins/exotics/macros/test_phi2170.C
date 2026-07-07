void test_phi2170(
    Int_t decay_mode = 0,     // decay channel (see below)
    Int_t nev = 1000,         // number of events
    Double_t beamE = 29.0     // proton beam kinetic energy [GeV]
){
    ///////////////////////////////////////////////////////////
    //
    // Example reaction channels currently used for the CBM
    // φ(2170) feasibility studies.
    //
    // decay_mode:
    //   0 -> φ π+ π−
    //   1 -> K+ K− π+ π−
    //   2 -> φ f0(980)
    //
    // Additional decay channels can be added as needed.
    //
    ///////////////////////////////////////////////////////////

    TString reaction;
    TString outfile;
    TString mode_name;

    switch (decay_mode) {

        case 0:
            reaction = "p p phi2170 [phi [K+ K-] pi+ pi-]";
            outfile  = "phi2170_phipipi";
            mode_name = "phi pi+ pi-";
            break;

        case 1:
            reaction = "p p phi2170 [K+ K- pi+ pi-]";
            outfile  = "phi2170_KKpipi";
            mode_name = "K+ K- pi+ pi-";
            break;

        case 2:
            reaction = "p p phi2170 [phi [K+ K-] f0_980 [pi+ pi-]]";
            outfile  = "phi2170_phif0";
            mode_name = "phi f0(980)";
            break;

        default:
            Error("test_phi2170",
                  "Unknown decay mode %d (allowed: 0, 1, 2)",
                  decay_mode);
            return;
    }

    PReaction r(beamE,
                "p",
                "p",
                reaction.Data(),
                outfile.Data());

    listParticle("f0_980");
    listParticle("phi2170");

    cout << endl;
    cout << "==========================================" << endl;
    cout << "phi(2170) example generation" << endl;
    cout << "==========================================" << endl;
    cout << "Beam energy : " << beamE << " GeV" << endl;
    cout << "Events      : " << nev << endl;
    cout << "Decay mode  : " << decay_mode << " (" << mode_name << ")" << endl;
    cout << "Reaction    : " << reaction << endl;
    cout << "Output      : " << outfile << ".root" << endl;
    cout << "==========================================" << endl;
    cout << endl;
    cout << "Inspect with : root -l -q 'inspect_phi2170.C(\"" << outfile << ".root\")'" << endl;
    cout << endl;
    cout << "==========================================" << endl;
    cout << endl;

    r.Print();

    r.Loop(nev);
}