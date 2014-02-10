#ifndef NSEventAction_h
#define NSEventAction_h 1

#include "globals.hh"
#include "G4UserEventAction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"
#include "G4UImanager.hh"
#include "G4RunManager.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UserSteppingAction.hh"
#include "G4UImessenger.hh"
#include "G4Run.hh"


class NSEventAction : public G4UserEventAction
{
private:
  G4double fEdep, fEini, fElast;
  bool first;

public:
  void BeginOfEventAction(const G4Event *event);
  void EndOfEventAction(const G4Event *event);

  void Register(const G4Step*);
};

#endif
