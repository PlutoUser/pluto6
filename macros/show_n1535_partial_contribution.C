{

    makeStaticData();
    //makeDataBase()->SetParamDouble ("NS110", "lmass", 0.);
    // makeDataBase()->SetParamDouble ("NS110", "umass", max);
    // makeDataBase()->SetParamInt ("NS110", "maxmesh",2000); 
    // makeDataBase()->SetParamInt ("N*(1535)0 --> p + pi-","maxmesh",2000); 
    // makeDataBase()->SetParamInt ("N*(1535)0 --> n + pi0","maxmesh",2000); 
    makeStaticData()->PrintParticle("NS11+");   
    makeDistributionManager()->Print();
    
    makeStaticData()->SetTotalNormalization("NS11+");
    
    // int cutoff_version=1; //urqmd
    int cutoff_version=0;
    
    makeDistributionManager()->LinkDB();
    PBreitWigner *n1535 = (PBreitWigner *) makeDistributionManager()->GetDistribution("NS110_bw");
    // ((PHadronDecay * )makeDistributionManager()->GetDistribution("NS110_fix_pi0_n"))->set_use_m0_over_m(1);
    //  ((PHadronDecay * )makeDistributionManager()->GetDistribution("NS110_fix_pi0_n"))->set_cutoff_version(cutoff_version);
    //  ((PHadronDecay * )makeDistributionManager()->GetDistribution("NS110_fix_pi-_p"))->set_use_m0_over_m(1);
    //  ((PHadronDecay * )makeDistributionManager()->GetDistribution("NS110_fix_pi-_p"))->set_cutoff_version(cutoff_version);
    //  ((PHadronDecay * )makeDistributionManager()->GetDistribution("NS110_fix_eta_n"))->set_use_m0_over_m(1);
    //  ((PHadronDecay * )makeDistributionManager()->GetDistribution("NS110_fix_eta_n"))->set_cutoff_version(cutoff_version);
    
    
    
    n1535->SetNpx(200);
    
    n1535->SetParameter(0, 0); //Mass
    //n1535->SetParameter(0, 1); //Width
    //n1535->SetParameter(1, -1);
    n1535->SetMinimum(0.00001);
    n1535->SetLineColor(1);
    n1535->Draw("");
    
    PBreitWigner *n1535_n_pi0 = (PBreitWigner *) n1535->Clone();
    PBreitWigner *n1535_1440  = (PBreitWigner *) n1535->Clone();
    PBreitWigner *n1535_eta   = (PBreitWigner *) n1535->Clone();
    n1535_n_pi0->SetParameter(1, 191); //parameter is the decay index
    n1535_1440->SetParameter(1, 201);
    n1535_eta->SetParameter(1, 192);
    
    n1535_n_pi0->SetLineStyle(9);
    n1535_n_pi0->SetLineWidth(2);
    n1535_n_pi0->SetLineColor(2);
    n1535_1440->SetLineStyle(7);
    n1535_1440->SetLineWidth(1.5);
    n1535_1440->SetLineColor(3);
    n1535_eta->SetLineStyle(10);
    n1535_eta->SetLineWidth(1.5);
    n1535_eta->SetLineColor(4);
    
    n1535_n_pi0->Draw("same");
    n1535_1440->Draw("same");
    n1535_eta->Draw("same");    
}


