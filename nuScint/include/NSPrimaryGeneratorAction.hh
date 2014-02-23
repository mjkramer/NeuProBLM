#ifndef NSPrimaryGeneratorAction_h
#define NSPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"

class G4Event;
class G4GeneralParticleSource;

class NSPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
public:
  virtual void GeneratePrimaries(G4Event*);
  NSPrimaryGeneratorAction();

private:
  G4GeneralParticleSource* fParticleGun;
};

#endif
