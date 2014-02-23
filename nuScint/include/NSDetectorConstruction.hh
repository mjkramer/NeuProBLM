#ifndef NSDetectorConstruction_h
#define NSDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"

class G4PhysicalVolume;

class NSDetectorConstruction : public G4VUserDetectorConstruction
{
public:
  virtual G4VPhysicalVolume* Construct();
};

#endif
