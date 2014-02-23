#include "G4RunManager.hh"
#include "G4UIterminal.hh"
#include "G4UIExecutive.hh"
#include "G4UItcsh.hh"
#include "G4VisExecutive.hh"
#include "G4RunManager.hh"

#include "NPRunManager.hh"

#include <iostream>
#include <vector>

using namespace std;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc, char** argv)
{
  if ( argc > 2 ) {
    cout << "Usage: " << argv[0] << " [macro]" << endl;
    return 1;
  }

  NPRunManager* runManager = new NPRunManager;

  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();

  // Get the pointer to the User Interface manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  if ( argc == 1 ) {
    // interactive mode
    G4UIExecutive* ui = new G4UIExecutive(argc, argv);
    UImanager->ApplyCommand("/control/execute vis.mac");
    ui->SessionStart();
    delete ui;
  } else {
    // batch mode
    UImanager->ApplyCommand(G4String("/control/execute ")+argv[1]);
  }

  delete visManager;
  delete runManager;
  return 0;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....



