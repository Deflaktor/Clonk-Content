
#strict

#include BRDG

public GetResearchBase: return(BRDG);

private func ControlElevator(string szCommand, object pObject)
{
  var pElev;
  // Objekte an dieser Position überprüfen
  while (pElev = FindObject(0, +1,+1,0,0, OCF_Grab(), 0,0, NoContainer(), pElev))
    // Im Fahrstuhlkorb
    if(pElev->~IsElevator())
      // Steuerung an Fahrstuhl weiterleiten
      return(ObjectCall(pElev,szCommand,pObject));
  return(0);
}

private func ControlElevatorMovement(string szCommand, object pObject)
{
  var pElev;
  // Objekte an dieser Position überprüfen
  while (pElev = FindObject(0, +1,+1,0,0, OCF_Grab(), 0,0, NoContainer(), pElev))
    // Fahrstuhlkorb gefunden
    if(pElev->~IsElevator())
      // Lore ist angehalten
      if (GetComDir() == COMD_Stop())
        // Steuerung an Fahrstuhl weiterleiten
        return(ObjectCall(pElev,szCommand,pObject));
  return(0);
}

private func ControlElevatorStop(string szCommand, object pObject)
{
  var pElev;
  // Objekte an dieser Position überprüfen
  while (pElev = FindObject(0, +1,+1,0,0, OCF_Grab(), 0,0, NoContainer(), pElev))
    // Fahrstuhlkorb gefunden
    if(pElev->~IsElevator())
      // Fahrstuhlkorb bewegt sich
      if (GetComDir(pElev) != COMD_Stop())
      {
        // Fahrstuhlkorb anhalten
        ObjectCall(pElev,szCommand,pObject); 
        // Noch nicht aussteigen
        SetComDir(COMD_Stop(), pObject);
        SetComDir(COMD_Stop());
        // Bewegunsbefehl abbrechen
        return(1);
      }
  return(0);
}