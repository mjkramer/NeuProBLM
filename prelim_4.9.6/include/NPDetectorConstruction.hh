#ifndef NPDetectorConstruction_h
#define NPDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "G4UImessenger.hh"

class G4VPhysicalVolume;

/// Detector construction class to define materials and geometry.

class NPDetectorConstruction : public G4VUserDetectorConstruction, public G4UImessenger
{

  public:
    virtual G4VPhysicalVolume* Construct();

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
