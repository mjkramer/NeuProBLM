#include <algorithm>
#include <cstdio>

#include "NSEventAction.hh"

#include "G4VPhysicalVolume.hh"
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"
#include "G4UImanager.hh"
#include "G4RunManager.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UserSteppingAction.hh"
#include "G4UImessenger.hh"
#include "G4Run.hh"

using namespace CLHEP;


NSEventAction::NSEventAction() :
  fKB(0), fFile(NULL), fTree(NULL)
{
  fFileNameCmd = new G4UIcmdWithAString("/NS/setFileName", this);
  fFileNameCmd->SetGuidance("Set file name");

  fKBCmd = new G4UIcmdWithADouble("/NS/setKB", this);
  fKBCmd->SetGuidance("Set Birks constant");
}

NSEventAction::~NSEventAction()
{
  if (fFile) {
    fTree->Write();
    fFile->Close();
  }
}

void NSEventAction::SetNewValue(G4UIcommand *cmd, G4String args)
{
  if (cmd == fFileNameCmd) {
    fFile = new TFile(args, "RECREATE");
    fTree = new TTree("tree", "tree");
    fTree->Branch("Nprotons", &fNprotons, "Nprotons/I");
    fTree->Branch("proEdep", fProtonEdep, "proEdep[Nprotons]/F");
    fTree->Branch("proEtrue", fProtonEtrue, "proEtrue[Nprotons]/F");
  } else if (cmd == fKBCmd) {
    fKB = fKBCmd->GetNewDoubleValue(args)/(cm/MeV);
  }
}

void NSEventAction::BeginOfEventAction(const G4Event*)
{
  fProtons.clear();

  // printf("\n***********************************\nNew event\n");
}
    
void NSEventAction::EndOfEventAction(const G4Event*)
{
  if (fTree) {
    fNprotons = fProtons.size();

    std::fill(fProtonEdep, fProtonEdep+fNprotons, 0);
    std::fill(fProtonEtrue, fProtonEtrue+fNprotons, 0);

    int i=0;
    for (std::map<G4Track*, Proton>::iterator it = fProtons.begin();
	 it != fProtons.end(); ++it, ++i) {
      Proton& p = it->second;
      fProtonEdep[i] = p.Edep;
      fProtonEtrue[i] = p.Etrue;
      // printf("Proton: Edep = %f, Etrue = %f\n", p.Edep, p.Etrue);
    }

    fTree->Fill();
  }
}

void NSEventAction::Register(G4Track* track, double e1, double e2, double dx)
{
  Proton& p = fProtons[track];

  if (p.Etrue == 0) {		// new proton
    p.Etrue = e1;
    // printf("Setting Etrue = %f\n", e1);
  }

  double Edep = (e1-e2) / (1 + fKB * (e1-e2)/dx);
  // printf("Adding Edep = %f\n", Edep);
  p.Edep += Edep;
}
