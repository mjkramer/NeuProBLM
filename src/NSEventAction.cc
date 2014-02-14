#include <iostream>

#include "NSEventAction.hh"

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

using namespace CLHEP;


NSEventAction::NSEventAction() :
  fFile(NULL), fTree(NULL)
{
  fFileNameCmd = new G4UIcmdWithAString("/NS/setFileName", this);
  fFileNameCmd->SetGuidance("Set file name");
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
    fTree->Branch("Edep", &fEdep);
  }
}

void NSEventAction::BeginOfEventAction(const G4Event*)
{
  fEdep = 0;
  fEini = 0;
  fElast = false;

  std::cout << "\n***********************************\nNew event\n";
}
    
void NSEventAction::EndOfEventAction(const G4Event*)
{
  // std::cout << "Total deposited: " << fEdep << " MeV" << std::endl << std::endl;

  if (fTree) {
    fTree->Fill();
  }
}

void NSEventAction::Register(const G4Step* step)
{
  G4VPhysicalVolume *preStepVol = step->GetPreStepPoint()->GetPhysicalVolume();
  G4VPhysicalVolume *postStepVol = step->GetPostStepPoint()->GetPhysicalVolume();

  double Ekin = step->GetTrack()->GetKineticEnergy()/MeV;

  if (preStepVol != NULL && postStepVol != NULL) {
    if (fEini == 0) fEini = fElast = Ekin;
    else {
      if (postStepVol->GetName() == "world" && fEdep == 0) {
	fEdep = fEini - fElast;
      } else {
	fElast = Ekin;
      }
    }
  }
}
