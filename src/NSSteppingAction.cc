#include <cstdio>

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

#include "NSSteppingAction.hh"

using namespace CLHEP;

void NSSteppingAction::UserSteppingAction(const G4Step *step)
{
  fEventAction->Register(step);

  G4StepPoint* preStepPt = step->GetPreStepPoint();
  G4StepPoint* postStepPt = step->GetPostStepPoint();

  double e1 = preStepPt->GetKineticEnergy()/MeV;
  double e2 = postStepPt->GetKineticEnergy()/MeV;
  double dx = (preStepPt->GetPosition() - postStepPt->GetPosition()).mag()/cm;

  G4VPhysicalVolume *preStepVol = preStepPt->GetPhysicalVolume();
  G4VPhysicalVolume *postStepVol = postStepPt->GetPhysicalVolume();

  G4String preName = preStepVol ? preStepVol->GetName() : G4String("NULL");
  G4String postName = postStepVol ? postStepVol->GetName() : G4String("NULL");

  G4String partName = step->GetTrack()->GetParticleDefinition()->GetParticleName();

  printf("Step (%s): %s (%f MeV) -> %s (%f MeV), dx = %f cm\n",
	 partName.data(), preName.data(), e1, postName.data(), e2, dx);

  // std::cout << "Step: " << preName << " -> " << postName << " " <<
  //   step->GetTrack()->GetKineticEnergy()/MeV << " MeV" <<
  //   " (" << partName << ")" << std::endl;
}
