#include <iostream>
#include "G4RunManager.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4PVPlacement.hh"
#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4GeneralParticleSource.hh"
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"
#include "G4UImanager.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4PhysListFactory.hh"
#include "G4Transform3D.hh"
#include "G4AssemblyVolume.hh"
#include "G4VisExecutive.hh"
#include "G4UserSteppingAction.hh"
#include "TTree.h"
#include "TFile.h"
#include "G4Track.hh"
#include "G4EventManager.hh"
#include "G4TrackingManager.hh"
#include "G4RunManager.hh"
#include "G4Run.hh"
#include "TString.h"
#include "G4Neutron.hh"
#include "G4VisAttributes.hh"
#include "G4Color.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "TUUID.h"

#include "NPRunManager.hh"

#include <vector>

using namespace std;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc, char** argv)
{
  if(argc > 2) {
    cout << "Usage: " << argv[0] << " [macro]" << endl;
    return 1;
  }
  NPRunManager* runManager = new NPRunManager;

  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();

  if(argc == 1) (new G4UIterminal(new G4UItcsh))->SessionStart();
  else G4UImanager::GetUIpointer()->ApplyCommand(G4String("/control/execute ")+argv[1]);

  delete visManager;
  delete runManager;
  return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....



