#ifndef NSSteppingAction_h
#define NSSteppingAction_h 1

#include "G4UserSteppingAction.hh"

#include "NSEventAction.hh"

class NSSteppingAction : public G4UserSteppingAction {
private:
  NSEventAction *fEventAction;

public:
  NSSteppingAction(NSEventAction *eventAction) :
    fEventAction(eventAction) {}

  void UserSteppingAction(const G4Step *step);
};

#endif
