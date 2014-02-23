
#include "NPSteppingAction.hh"
#include <iostream>
#include <fstream>

using namespace std;
using namespace CLHEP;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NPSteppingAction::NPSteppingAction() {

  ResetVars();
  fFileNameCmd = new G4UIcmdWithAString("/NP/setFileName", this);
  fFileNameCmd->SetGuidance("Set file name");

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NPSteppingAction::~NPSteppingAction() {

  if ( fFile ) {
    if ( fTEPIDs.size()>0 || fDEPIDs.size()>0) fTree->Fill();
    fTree->Write();
    fFile->Close();
  }
  delete fFileNameCmd;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NPSteppingAction::SetNewValue(G4UIcommand *command, G4String newValues) {

  if ( command == fFileNameCmd ) fFileName = newValues;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NPSteppingAction::ResetVars() {

  fTEPIDs.clear();
  fTEEnergies.clear();
  fTEMomentumCosTheta.clear();
  fDEPIDs.clear();
  fDEEnergies.clear();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NPSteppingAction::UserSteppingAction(const G4Step *step) {

  if ( fFile == NULL ) {     

    fNEvents 
      = G4RunManager::GetRunManager()->GetCurrentRun()->GetNumberOfEventToBeProcessed();
    if ( fFileName == "" ) {
      G4int muE_GeV_AsInt 
        = (G4int) rint(step->GetPreStepPoint()->GetKineticEnergy()/GeV);
      fFile 
        = TFile::Open(TString::Format("nuproblm_%dGeV.root", muE_GeV_AsInt), "recreate");
    } else fFile = TFile::Open(fFileName.c_str(), "recreate");
    fTree = new TTree("tree", "tree");
    fTree->Branch("nEvents", &fNEvents, "N/I");
    fTree->Branch("tePID", &fTEPIDs);
    fTree->Branch("teE", &fTEEnergies);
    fTree->Branch("tePCosQ", &fTEMomentumCosTheta);
    fTree->Branch("dePID", &fDEPIDs);
    fTree->Branch("deE", &fDEEnergies);
    ResetVars();

  }  else {

    G4int eventID 
      = G4EventManager::GetEventManager()->GetConstCurrentEvent()->GetEventID();
    static G4int lastEventID = eventID;
    if ( eventID != lastEventID ) {
      if ( fTEPIDs.size() > 0 || fDEPIDs.size() > 0 ) fTree->Fill();
      ResetVars();
      lastEventID = eventID;
    }

  }

  G4VPhysicalVolume* preStepVol  = step->GetPreStepPoint()->GetPhysicalVolume();
  G4VPhysicalVolume* postStepVol = step->GetPostStepPoint()->GetPhysicalVolume();

  if ( preStepVol != NULL && postStepVol != NULL ) {

    if ( preStepVol->GetName() == "target" && 
         postStepVol->GetName() == "world" ) {

      fTEPIDs.push_back(
        step->GetTrack()->GetParticleDefinition()->GetPDGEncoding());
      fTEEnergies.push_back(
        step->GetTrack()->GetKineticEnergy()/MeV);
      fTEMomentumCosTheta.push_back(
          step->GetTrack()->GetMomentumDirection().cosTheta());
      fDEPIDs.push_back(-999);
      fDEEnergies.push_back(-999);

    } else if ( preStepVol->GetName() == "world" &&
                postStepVol->GetName() == "detector" ) {

      fTEPIDs.push_back(-999);
      fTEEnergies.push_back(-999);
      fTEMomentumCosTheta.push_back(-999);
      fDEPIDs.push_back(
        step->GetTrack()->GetParticleDefinition()->GetPDGEncoding());
      fDEEnergies.push_back(
        step->GetTrack()->GetKineticEnergy()/MeV);

    }

  }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

