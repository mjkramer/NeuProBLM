#include <iostream>

#include "G4PhysListFactory.hh"

#include "NSRunManager.hh"
#include "NSDetectorConstruction.hh"
#include "NSSteppingAction.hh"
#include "NSEventAction.hh"
#include "NSPrimaryGeneratorAction.hh"

NSRunManager::NSRunManager() {
  SetUserInitialization(new NSDetectorConstruction);
  SetUserInitialization((new G4PhysListFactory)
			->GetReferencePhysList("QGSP_BERT_HP"));

  SetUserAction(new NSPrimaryGeneratorAction);
  NSEventAction *eventAction = new NSEventAction;
  SetUserAction(eventAction);
  SetUserAction(new NSSteppingAction(eventAction));

  fDirectory = new G4UIdirectory("/NS/");
  fDirectory->SetGuidance("Parameters for nuScint");

  fSeedWithTimeCmd = new G4UIcmdWithoutParameter("/NS/seedWithTime", this);
  fSeedWithTimeCmd->SetGuidance("Seed RNG with UNIX time");
}

NSRunManager::~NSRunManager() {
}

void NSRunManager::SetNewValue(G4UIcommand *cmd, G4String args)
{
  if (cmd == fSeedWithTimeCmd) {
    int seed = time(0);
    G4Random::setTheSeed(seed);
    std::cout << "Seed: " << seed << std::endl;
  } else if (cmd == fSeedCmd) {
    G4int seed = fSeedCmd->GetNewIntValue(args);
    G4Random::setTheSeed(seed);
    std::cout << "Seed: " << seed << std::endl;
  }
}
