#ifndef NPPrimaryGeneratorAction_h
#define NPPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4GeneralParticleSource.hh"

class G4ParticleGun;
class G4Event;
class NPDetectorConstruction;

class NPPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{

  public:
    virtual void GeneratePrimaries(G4Event*);

  private:
    G4GeneralParticleSource* fParticleGun;

};

#endif
