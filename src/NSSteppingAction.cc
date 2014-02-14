#include <iostream>

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

  G4VPhysicalVolume *preStepVol = step->GetPreStepPoint()->GetPhysicalVolume();
  G4VPhysicalVolume *postStepVol = step->GetPostStepPoint()->GetPhysicalVolume();

  G4String preName = preStepVol ? preStepVol->GetName() : G4String("NULL");
  G4String postName = postStepVol ? postStepVol->GetName() : G4String("NULL");

  // std::cout << "Step: " << preName << " -> " << postName << " " <<
  //   step->GetTrack()->GetKineticEnergy()/MeV << " MeV" << std::endl;
}
