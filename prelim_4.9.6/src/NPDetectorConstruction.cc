
#include "NPDetectorConstruction.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* NPDetectorConstruction::Construct()
{

  G4Material* vacuum
    = G4NistManager::Instance()->FindOrBuildMaterial("G4_Galactic", false);
  G4Material* targetMat
    = G4NistManager::Instance()->FindOrBuildMaterial("G4_Pb", false);
  G4Material* detectorMat 
    = G4NistManager::Instance()->FindOrBuildMaterial("G4_POLYETHYLENE", false);

  /*
  http://www.eljentechnology.com/index.php/joomla-overview/this-is-newest/73-ej-309
  http://www.eljentechnology.com/images/stories/Data_Sheets/Liquid_Scintillators/EJ309%20data%20sheet.pdf
  ATOMIC COMPOSITION
  No. of H Atoms per cm3 5.43 x 10 22
  No. of C Atoms per cm 3 4.35 x 10 22
  H:C. Ratio 1.25
  No. of Electrons per cm 3 3.16 x 10 23
  */

  G4VisAttributes* copperVisAtt 
    = new G4VisAttributes(G4Colour(173./256., 111./256., 105./256.));
  G4VisAttributes* glassVisAtt 
    = new G4VisAttributes(G4Colour(0.5, 0.5, 0.5, 0.3));

  // world
  G4Box* worldBox = new G4Box("worldBox", 10.0*m, 10.0*m, 10.0*m);
  G4LogicalVolume* worldL = new G4LogicalVolume(worldBox, vacuum, "worldL");
  worldL->SetVisAttributes(G4VisAttributes::Invisible);
  G4VPhysicalVolume* physWorld =
    new G4PVPlacement(0, G4ThreeVector(), worldL, "world", 0, false, 0, true);                 

  // target
  G4double inch = 2.54*cm;
  G4Box* targetS = new G4Box("targetS", 2.*inch, 2.*inch, 4.*inch);
  G4LogicalVolume* targetL = new G4LogicalVolume(targetS, targetMat, "targetL");
  targetL->SetVisAttributes(copperVisAtt);
  new G4PVPlacement(G4Transform3D::Identity, targetL, "target", worldL, false, 0, true);

  // detector
  G4Tubs* detectorS = new G4Tubs("detectorS", 0, 2.5*inch, 2.5*inch, 0, 2.0*pi);
  G4LogicalVolume* detectorL 
    = new G4LogicalVolume(detectorS, detectorMat, "detectorL");
  detectorL->SetVisAttributes(glassVisAtt);
  G4Transform3D detectorPosRot = G4RotateY3D(90.*degree)*G4TranslateZ3D(1.5*m);
  new G4PVPlacement(detectorPosRot, detectorL, "detector", worldL, false, 0, true);

  return physWorld;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......



