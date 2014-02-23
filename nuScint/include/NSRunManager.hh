#ifndef NSRunManager_h
#define NSRunManager_h 1

#include "G4RunManager.hh"
#include "globals.hh"
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"
#include "G4UImanager.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithoutParameter.hh"


class NSRunManager : public G4RunManager, public G4UImessenger
{
public:
  NSRunManager();
  ~NSRunManager();

  void SetNewValue(G4UIcommand *cmd, G4String args);

private:
  G4UIdirectory* fDirectory;
  G4UIcmdWithoutParameter* fSeedWithTimeCmd;
  G4UIcmdWithAnInteger* fSeedCmd;
};

#endif
