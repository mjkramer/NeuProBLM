
#include "NPPrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4GeneralParticleSource.hh"
#include "G4ParticleGun.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
NPPrimaryGeneratorAction::NPPrimaryGeneratorAction()
{
  fParticleGun = new G4GeneralParticleSource();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void NPPrimaryGeneratorAction::GeneratePrimaries(G4Event* event)
{
  fParticleGun->GeneratePrimaryVertex(event);
}



