#ifndef NPRunManager_h
#define NPRunManager_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"
#include "G4UImanager.hh"
#include "G4RunManager.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4PhysListFactory.hh"
#include <iostream>
#include <fstream>

class NPRunManager : public G4RunManager, public G4UImessenger
{
  private:
    G4UIdirectory* fDirectory;
    G4UIcmdWithAString* fPhysListCmd;
    G4UIcmdWithoutParameter* fSeedWithUUIDCmd;

  public:
    NPRunManager();
    ~NPRunManager();

    void SetNewValue(G4UIcommand *command, G4String newValues);
};                   

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
