///////////////////////////////////////////////////////////////
//
// inspect_phi2170.C
//
// Example analysis macro for the exotic particle plugin.
//
// Reads the ROOT file produced by test_phi2170.C and
// demonstrates how to:
//
//   - read the Pluto event tree
//   - access PParticle objects
//   - reconstruct simple invariant masses
//   - draw basic histograms
//
///////////////////////////////////////////////////////////////

{
    //----------------------------------------------------------
    // Register exotic particles (e.g. phi2170, f0_980)
    //----------------------------------------------------------

    makeDistributionManager()->Exec("exotics:init");

    //----------------------------------------------------------
    // Open ROOT file
    //----------------------------------------------------------

    TFile *f = TFile::Open("test_phi2170.root");

    if (!f || f->IsZombie()) {
        cout << "Cannot open test_phi2170.root" << endl;
        return;
    }

    TTree *tree = (TTree*)f->Get("data");

    if (!tree) {
        cout << "Tree \"data\" not found." << endl;
        return;
    }

    //----------------------------------------------------------
    // Read Pluto particle array
    //----------------------------------------------------------

    TClonesArray *particles = nullptr;
    tree->SetBranchAddress("Particles", &particles);

    //----------------------------------------------------------
    // Retrieve particle IDs from the Pluto particle database
    //----------------------------------------------------------

    Int_t pidKp  = makeStaticData()->GetParticleID("K+");   // particle ID 11
    Int_t pidKm  = makeStaticData()->GetParticleID("K-");   // particle ID 12
    Int_t pidPip = makeStaticData()->GetParticleID("pi+");  // particle ID 8
    Int_t pidPim = makeStaticData()->GetParticleID("pi-");  // particle ID 9

    //----------------------------------------------------------
    // Histograms
    //----------------------------------------------------------

    TH1D *h_mKK = new TH1D(
        "h_mKK",
        "K^{+}K^{-} invariant mass;M(K^{+}K^{-}) [GeV/c^{2}];Events",
        100, 0.95, 1.10);

    TH1D *h_mpipi = new TH1D(
        "h_mpipi",
        "#pi^{+}#pi^{-} invariant mass;M(#pi^{+}#pi^{-}) [GeV/c^{2}];Events",
        100, 0.2, 1.5);

    TH1D *h_mKKpipi = new TH1D(
        "h_mKKpipi",
        "K^{+}K^{-}#pi^{+}#pi^{-} invariant mass;M(K^{+}K^{-}#pi^{+}#pi^{-}) [GeV/c^{2}];Events",
        120, 1.8, 2.5);

    //----------------------------------------------------------
    // Event loop
    //----------------------------------------------------------

    Long64_t nev = tree->GetEntries();

    cout << "Reading " << nev << " events..." << endl;

    for (Long64_t iev = 0; iev < nev; iev++) {

        tree->GetEntry(iev);

        if (!particles) continue;

        TLorentzVector kp, km, pip, pim;

        bool hasKp  = false;
        bool hasKm  = false;
        bool hasPip = false;
        bool hasPim = false;

        Int_t np = particles->GetEntriesFast();

        //------------------------------------------------------
        // Loop over all particles in the event
        //------------------------------------------------------

        for (Int_t i = 0; i < np; i++) {

            PParticle *p = (PParticle*)particles->At(i);

            if (p->ID() == pidKp) {
                kp = *p;
                hasKp = true;
            }
            else if (p->ID() == pidKm) {
                km = *p;
                hasKm = true;
            }
            else if (p->ID() == pidPip) {
                pip = *p;
                hasPip = true;
            }
            else if (p->ID() == pidPim) {
                pim = *p;
                hasPim = true;
            }
        }

        //------------------------------------------------------
        // Fill invariant-mass histograms
        //------------------------------------------------------

        if (hasKp && hasKm) {

            h_mKK->Fill((kp + km).M());

            if (hasPip && hasPim) {

                h_mpipi->Fill((pip + pim).M());

                h_mKKpipi->Fill((kp + km + pip + pim).M());
            }
        }
    }

    //----------------------------------------------------------
    // Draw histograms
    //----------------------------------------------------------

    TCanvas *c = new TCanvas("c", "phi2170 inspect", 1200, 400);

    c->Divide(3,1);

    c->cd(1);
    h_mKK->Draw();

    c->cd(2);
    h_mpipi->Draw();

    c->cd(3);
    h_mKKpipi->Draw();

    c->SaveAs("phi2170_inspect.pdf");

    cout << endl;
    cout << "Inspection finished." << endl;
    cout << "Plots saved to phi2170_inspect.pdf" << endl;
}