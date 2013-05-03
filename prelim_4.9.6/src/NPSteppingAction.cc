
#include "NPSteppingAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NPSteppingAction::NPSteppingAction() {

  ResetVars();
  fFileNameCmd = new G4UIcmdWithAString("/NP/setFileName", this);
  fFileNameCmd->SetGuidance("Set file name");

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NPSteppingAction::~NPSteppingAction() {

  if(fFile) {
    if(fDetectorE>0 || fTEPIDs.size()>0 || fDEPIDs.size()>0) fTree->Fill();
    fTree->Write();
    fFile->Close();
  }
  delete fFileNameCmd;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NPSteppingAction::SetNewValue(G4UIcommand *command, G4String newValues) {

  if(command == fFileNameCmd) fFileName = newValues;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NPSteppingAction::ResetVars() {

  fDetectorE = 0;
  fTEPIDs.clear();
  fTEEnergies.clear();
  fTEMomentumCosTheta.clear();
  fDEPIDs.clear();
  fDEEnergies.clear();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NPSteppingAction::UserSteppingAction(const G4Step *step) {

  if(fFile == NULL) {
    fNEvents 
      = G4RunManager::GetRunManager()->GetCurrentRun()->GetNumberOfEventToBeProcessed();
    if(fFileName == "") {
      G4int muE_GeV_AsInt 
        = (G4int) rint(step->GetPreStepPoint()->GetKineticEnergy()/GeV);
      fFile 
        = TFile::Open(TString::Format("nuproblm_%dGeV.root", muE_GeV_AsInt), "recreate");
    }
    else fFile = TFile::Open(fFileName.c_str(), "recreate");
    fTree = new TTree("tree", "tree");
    fTree->Branch("nEvents", &fNEvents, "N/I");
    fTree->Branch("detectorE_MeV", &fDetectorE, "E/D");
    fTree->Branch("tePID", &fTEPIDs);
    fTree->Branch("teE", &fTEEnergies);
    fTree->Branch("tePCosQ", &fTEMomentumCosTheta);
    fTree->Branch("dePID", &fDEPIDs);
    fTree->Branch("deE", &fDEEnergies);
    ResetVars();
  }
  else {
    G4int eventID 
      = G4EventManager::GetEventManager()->GetConstCurrentEvent()->GetEventID();
    static G4int lastEventID = eventID;
    if(eventID != lastEventID) {
      if(fDetectorE>0 || fTEPIDs.size()>0 || fDEPIDs.size()>0) fTree->Fill();
      ResetVars();
      lastEventID = eventID;
    }
  }

  G4double energyDep = step->GetTotalEnergyDeposit();
  fDetectorE += energyDep/MeV;

  G4VPhysicalVolume* preStepVol = step->GetPreStepPoint()->GetPhysicalVolume();
  G4VPhysicalVolume* postStepVol = step->GetPostStepPoint()->GetPhysicalVolume();
  if(preStepVol != postStepVol) {
    static G4VPhysicalVolume* world = NULL;
    static G4VPhysicalVolume* target = NULL;
    static G4VPhysicalVolume* detector = NULL;
    if(preStepVol != world && preStepVol != target && preStepVol != detector) {
      if(world == NULL && preStepVol->GetName() == "world") world = preStepVol;
      else if(target == NULL && preStepVol->GetName() == "target") target = preStepVol;
      else if(detector == NULL && preStepVol->GetName() == "detector") detector = preStepVol;
    }
    if(postStepVol != world && postStepVol != target && postStepVol != detector) {
      if(world == NULL && postStepVol->GetName() == "world") world = postStepVol;
      else if(target == NULL && postStepVol->GetName() == "target") target = postStepVol;
      else if(detector == NULL && postStepVol->GetName() == "detector") detector = postStepVol;
    }

    // target exiters
    if(preStepVol == target && postStepVol == world) {
      fTEPIDs.push_back(step->GetTrack()->GetParticleDefinition()->GetPDGEncoding());
      fTEEnergies.push_back(step->GetTrack()->GetKineticEnergy()/MeV);
      fTEMomentumCosTheta.push_back(step->GetTrack()->GetMomentumDirection().cosTheta());
    }
    // detector enterers
    else if(preStepVol == world && postStepVol == detector) {
      fDEPIDs.push_back(step->GetTrack()->GetParticleDefinition()->GetPDGEncoding());
      fDEEnergies.push_back(step->GetTrack()->GetKineticEnergy()/MeV);
    }
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......





