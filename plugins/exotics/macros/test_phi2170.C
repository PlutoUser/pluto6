{
    // Example reactions currently used for the CBM φ(2170) feasibility studies.
    // Additional decay channels can be added as needed.

    Int_t decay_mode = 0;
    double beamE = 29.0;
    int nev = 1000;
    
    TString reaction;
    if(decay_mode==0) {
	reaction = "p p phi2170 [phi [K+ K-] pi+ pi-]";
    } else if(decay_mode==1) {
        reaction = "p p phi2170 [K+ K- pi+ pi-]";
    } else if(decay_mode==2) {
        reaction = "p p phi2170 [phi [K+ K-] f0_980 [pi+ pi-]]";
    }

    PReaction r(beamE, "p", "p", reaction.Data(), "test_phi2170");

    listParticle("f0_980");
    listParticle("phi2170");
    
    cout << "Reaction: " << reaction << endl;

    r.Print();
    r.Loop(nev);    
}
