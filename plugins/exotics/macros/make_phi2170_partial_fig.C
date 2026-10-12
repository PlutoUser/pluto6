{


    TCanvas *c1 = new TCanvas("c1", "phi(2170) mass distribution", 800, 800);
    c1->SetLogy(1);
    
    //acticate the plugin in advance:
    makeDistributionManager()->Exec("exotics:init");
    //loop over std physics to generate the model objects
    makeDistributionManager()->ActivateStdModels();
    //check if it worked:
    listParticle("phi2170");

    //get the decay indices:
    Int_t phi2170_to_phi_pipi_idx = makeStaticData()->GetDecayIdx("phi2170", "phi, pi+, pi-");
    Int_t phi2170_to_KKpipi_idx   = makeStaticData()->GetDecayIdx("phi2170", "K+, K-, pi+, pi-");
    Int_t phi2170_to_phif0_idx    = makeStaticData()->GetDecayIdx("phi2170", "phi, f0_980");
    
    //the name of the distributions as obtained with listParticle
    PBreitWigner *phi2170             = dynamic_cast<PBreitWigner*>(makeDistributionManager()->GetDistribution("phi2170_bw")->Clone());
    PBreitWigner *phi2170_to_phi_pipi = dynamic_cast<PBreitWigner*>(phi2170->Clone());
    PBreitWigner *phi2170_to_KKpipi   = dynamic_cast<PBreitWigner*>(phi2170->Clone());
    PBreitWigner *phi2170_to_phif0    = dynamic_cast<PBreitWigner*>(phi2170->Clone());
    phi2170->SetParameter(0, 0);
    phi2170->SetParameter(1, -1);
    phi2170->SetName("total");
    phi2170_to_phi_pipi->SetParameter(1, phi2170_to_phi_pipi_idx);
    phi2170_to_phi_pipi->SetName("phi_pipi");
    phi2170_to_KKpipi->SetParameter(1, phi2170_to_KKpipi_idx);
    phi2170_to_KKpipi->SetName("KKpipi");
    phi2170_to_phif0->SetParameter(1, phi2170_to_phif0_idx);
    phi2170_to_phif0->SetName("phif0");

    //dummy to create the meshes
    Double_t mass;
    phi2170->GetWidth(2.2,&mass);

    phi2170_to_phi_pipi->SetLineColor(1); //pipi black
    phi2170_to_phif0->SetLineColor(3); //phif0 green
    
    phi2170_to_phi_pipi->Draw();
    phi2170_to_phi_pipi->SetTitle("phi(2170) mass distribution");
    phi2170_to_KKpipi->Draw("same");
    phi2170_to_phif0->Draw("same");


}
