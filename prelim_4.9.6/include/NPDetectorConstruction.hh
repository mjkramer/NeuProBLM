#ifndef NPDetectorConstruction_h
#define NPDetectorConstruction_h 1

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

class G4VPhysicalVolume;

/// Detector construction class to define materials and geometry.

class NPDetectorConstruction : public G4VUserDetectorConstruction, public G4UImessenger
{
  public:
    virtual G4VPhysicalVolume* Construct();
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
