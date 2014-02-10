#include <cstring>
#include <iostream>

#include <TROOT.h>
#include "G4UIExecutive.hh"
#include "G4UIterminal.hh"
#include "G4UIExecutive.hh"
#include "G4UItcsh.hh"
#include "G4VisExecutive.hh"

#include "NSRunManager.hh"

int main(int argc, char** argv)
{
  char* macroFile;
  bool vis = false;

  if (!strcmp(argv[1], "-v")) {	// \o/ segfault!
    vis = true;
    macroFile = argv[2];
  } else {
    macroFile = argv[1];
  }

  NSRunManager* runManager = new NSRunManager;

  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();

  G4UImanager* uiManager = G4UImanager::GetUIpointer();

  char* execCmd = Form("/control/execute %s", macroFile);

  if (vis) {
    G4UIExecutive *uiExec = new G4UIExecutive(argc, argv);
    uiManager->ApplyCommand(execCmd);
    uiExec->SessionStart();
  } else {
    uiManager->ApplyCommand(execCmd);
  }

  delete runManager;

  return 0;
}
    
