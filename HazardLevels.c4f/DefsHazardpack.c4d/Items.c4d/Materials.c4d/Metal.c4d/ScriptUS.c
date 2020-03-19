/*-- Metal --*/

Hit:
  Sound("MetalHit*");
  return(1);

Activate:
  [Build metal bridge]
  // Clonk soll anhalten
	SetComDir(COMD_Stop(),Par(0));
  // Menü öffnen
  CreateMenu(MTMS,Par(0),this());
  AddMenuItem("%s","MenuBridge",MTM1,Par(0));
  AddMenuItem("%s","MenuBridge",MTM2,Par(0));
  AddMenuItem("%s","MenuBridge",MTM3,Par(0));
  AddMenuItem("%s","MenuBridge",MTM4,Par(0));
  AddMenuItem("%s","MenuBridge",MTM5,Par(0));
  // Vorauswahl Senkrecht
  SelectMenuItem(2,Par(0));
	return(1);

MenuBridge:
  // Aktion setzen
  ObjectSetAction(Contained(),"Bridge");
  // Richtung setzen
  if (Equal(Par(0),MTM1)) SetComDir(COMD_Left(),Contained());
  if (Equal(Par(0),MTM2)) SetComDir(COMD_UpLeft(),Contained());
  if (Equal(Par(0),MTM3)) SetComDir(COMD_Up(),Contained());
  if (Equal(Par(0),MTM4)) SetComDir(COMD_UpRight(),Contained());
  if (Equal(Par(0),MTM5)) SetComDir(COMD_Right(),Contained());
  // Brückenmaterial setzen
  SetActionData(Material("Granite"),Contained());
  // Material verbrauchen
  RemoveObject();
  // Fertig
  return(1);