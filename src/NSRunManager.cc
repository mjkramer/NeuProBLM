#include "G4PhysListFactory.hh"

#include "NSRunManager.hh"
#include "NSDetectorConstruction.hh"
#include "NSSteppingAction.hh"
#include "NSEventAction.hh"
#include "NSPrimaryGeneratorAction.hh"

// #include <ctime>		// cstdlib?

NSRunManager::NSRunManager() {
  SetUserInitialization(new NSDetectorConstruction);
  SetUserInitialization((new G4PhysListFactory)
			->GetReferencePhysList("QGSP_BERT_HP"));

  SetUserAction(new NSPrimaryGeneratorAction);
  NSEventAction *eventAction = new NSEventAction;
  SetUserAction(eventAction);
  SetUserAction(new NSSteppingAction(eventAction));

  CLHEP::HepRandom::setTheSeed(time(0));
}

NSRunManager::~NSRunManager() {
}


