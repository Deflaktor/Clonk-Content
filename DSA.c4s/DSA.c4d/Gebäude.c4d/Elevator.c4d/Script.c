/*-- Fahrstuhl --*/

#strict

#include CXEC

protected func Initialize()
  {
  var pCase = CreateObject(ELEC,+0,+27,GetOwner());
  SetObjectOrder(this(), pCase);
  SetAction("LiftCase",pCase);
  return(1);
  }

public func RemoveCase()
  {
  // Komplett, aber kein Fahrstuhlkorb: reduzieren für Wiederaufbau/Reparatur
  if (GetCon() == 100) { SetAction("Idle"); DoCon(-1); }
  return(1);
  }

// Zum externen Aufruf von Szenarienscripten
public func CreateShaft(iLength)
  {
  // SolidMask des ELEC wegschieben
  var pCase, iCaseY;
  if (pCase = GetActionTarget())
    {
    iCaseY = GetY(pCase);
    SetPosition(GetX(pCase), GetY() - 20, pCase);
    }
  // Schacht freigraben
  DigFreeRect(GetX()-12, GetY()+25, 24, iLength);
  // ELEC zurückschieben
  if(pCase) SetPosition(GetX(pCase), iCaseY, pCase);
  return(1);
  }
