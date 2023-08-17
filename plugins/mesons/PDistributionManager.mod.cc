//this line is added to the PDistributionManager.cc

PMesonsPlugin *mesons = new PMesonsPlugin("mesons", "Mesons extension");
AddPlugin(mesons);
Enable("mesons");
PluginInfo("Various mesons available");

