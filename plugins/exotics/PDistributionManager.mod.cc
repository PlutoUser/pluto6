//this is added to the PDistributionManager.cc:

PExoticsPlugin *exotics = new PExoticsPlugin("exotics", "Extension for exotic candidates like molecules, glueballs");
AddPlugin(exotics);
Enable("exotics");
PluginInfo("Exotic particles available");

