#include "NSPrimaryGeneratorAction.hh"

#include "G4GeneralParticleSource.hh"

NSPrimaryGeneratorAction::NSPrimaryGeneratorAction()
{
  fParticleGun = new G4GeneralParticleSource();
}

void NSPrimaryGeneratorAction::GeneratePrimaries(G4Event* event)
{
  fParticleGun->GeneratePrimaryVertex(event);
}
