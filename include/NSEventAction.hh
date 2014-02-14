#ifndef NSEventAction_h
#define NSEventAction_h 1

#include <TFile.h>
#include <TTree.h>

#include "globals.hh"
#include "G4UserEventAction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"
#include "G4UImanager.hh"
#include "G4RunManager.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UImessenger.hh"
#include "G4Run.hh"


class NSEventAction : public G4UserEventAction, public G4UImessenger
{
public:
  NSEventAction();
  ~NSEventAction();

  void BeginOfEventAction(const G4Event *event);
  void EndOfEventAction(const G4Event *event);
  void SetNewValue(G4UIcommand *cmd, G4String args);

  void Register(const G4Step*);

private:
  G4double fEdep, fEini, fElast;
  bool first;

  G4UIcmdWithAString *fFileNameCmd;
  TFile *fFile;
  TTree *fTree;
};

#endif
