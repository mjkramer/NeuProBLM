
#include "NPRunManager.hh"
#include "NPDetectorConstruction.hh"
#include "NPSteppingAction.hh"
#include "NPPrimaryGeneratorAction.hh"
#include <iostream>
#include <fstream>

using namespace std;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NPRunManager::NPRunManager() {

  SetUserInitialization(new NPDetectorConstruction);

  fDirectory = new G4UIdirectory("/NP/");
  fDirectory->SetGuidance("Parameters for NP MC");

  fPhysListCmd = new G4UIcmdWithAString("/NP/setReferencePhysList", this);
  fPhysListCmd->SetGuidance("Set reference physics list to be used");
  //fPhysListCmd->SetCandidates("Shielding ShieldingNoRDM QGSP_BERT_HP");

  fSeedWithUUIDCmd = new G4UIcmdWithoutParameter("/NP/seedWithUUID", this);
  fSeedWithUUIDCmd->SetGuidance("Seed random number generator quickly with an almost random number");
  fSeedWithUUIDCmd->SetGuidance("Generated using ROOT's TUUID class");

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NPRunManager::~NPRunManager() {

  delete fDirectory;
  delete fPhysListCmd;
  delete fSeedWithUUIDCmd;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NPRunManager::SetNewValue(G4UIcommand *command, G4String newValues) {

  if(command == fPhysListCmd) {
    SetUserInitialization((new G4PhysListFactory)->GetReferencePhysList(newValues));
    SetUserAction(new NPSteppingAction);
    SetUserAction(new NPPrimaryGeneratorAction);
  }
  else if(command == fSeedWithUUIDCmd) {
    TUUID uuid;
    UInt_t buffer[4];
    uuid.GetUUID((UChar_t*) buffer);
    long seed = (buffer[0] + buffer[1] + buffer[2] + buffer[3]);
    if (seed < 0) seed = -seed;
    CLHEP::HepRandom::setTheSeed(seed);
    cout << "CLHEP::HepRandom seed set to: " << seed << endl;
  }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
