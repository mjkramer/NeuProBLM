
#ifndef NPSteppingAction_h
#define NPSteppingAction_h 1

#include "TFile.h"
#include "TTree.h"
#include <vector>
#include <iostream>

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
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

class NPSteppingAction : public G4UserSteppingAction, public G4UImessenger
{
  protected:
    G4UIcmdWithAString* fFileNameCmd;
    std::string fFileName;
    TFile* fFile;
    TTree* fTree;

    G4int fNEvents;

    // target exiters
    std::vector<G4int> fTEPIDs; // target exiter particle IDs
    std::vector<G4double> fTEEnergies;
    std::vector<G4double> fTEMomentumCosTheta;

    // detector enterers
    std::vector<G4int> fDEPIDs; // detector interactors particle IDs
    std::vector<G4double> fDEEnergies;

  public:
    ///NPSteppingAction() : fFile(NULL), fTree(NULL), fNEvents(0);
    NPSteppingAction();
    ~NPSteppingAction();

    void SetNewValue(G4UIcommand *command, G4String newValues);
    void ResetVars();

    void UserSteppingAction(const G4Step *step);

};

#endif
