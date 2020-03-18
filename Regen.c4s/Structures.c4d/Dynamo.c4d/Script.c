/*-- Dynamo --*/

#strict
#include BAS2

/* Steuerung */

public func ContextProduction(pCaller)
{
  [$TxtEnergy$|Image=RSR1|Condition=IsBuilt]
  return(StartWork(pCaller));
}

protected func IsBuilt() {
  return(GetCon() >= 100);
}

LineConnectType:
  return(PWR2);

func ContainedThrow() { return(1); }
  
public func ControlDigDouble(pCaller)
{
  [$TxtProduce$|Image=RSR1]
  return(StartWork(pCaller));
}

public func ContainedDown(pCaller)
{
  [$TxtCancelproduction$|Image=RSR2]
  WorkCancel(pCaller);
  return(1);
}

func StartWork(pWorker)
  {
  if(GetAction() eq "Working") return(Message("$TxtAlreadyInUse$", pWorker)); 
  // Arbeit beginnen
  AddCommand(pWorker,"Call",this(),0,0,0, 0, "Work", 0, 1);  
  // Vorher: Position einnehmen
  AddCommand(pWorker,"MoveTo",0,GetX()+10,GetY());
  }

func Work(pWorker)
  {
  // Clonk einsaugen
  Enter(this(),pWorker);
  // Besitzer setzen für Farbe des animierten Clonk
  SetOwner(GetOwner(pWorker));
  // Farbe nach Clonkfarbe richten
  SetColorDw(GetColorDw(pWorker));
  // Aktion starten
  SetAction("Working");
  return(1);
  }

func Working()
  {
  // Ich bin ja ein vielbeschäftigter Timer
  var obj = FindObject(0,0,0,0,0,OCF_CrewMember(),0,0,this());
  if(!obj) return(SetAction("Idle"));
  if(!GetAlive(obj)) return(WorkCancel(obj));
  if(GetCommand(obj)) return(WorkCancel(obj));
  CheckForSolid();
  if(GetEnergy()<10)
   DoEnergy(+1);
  return(1);
  }

func CheckForSolid()
  {
  if(GBackSemiSolid()) return(WorkCancel());
  }

private func WorkCancel(pWorker)
  {
  if(!pWorker) pWorker=FindObject(0,0,0,0,0,OCF_CrewMember(),0,0,this());
  // Arbeit abbrechen
  if (GetAction() eq "Working") SetAction("Idle");
  Exit(pWorker,10,10);
  SetDir(DIR_Left(), pWorker);
  // Fertig
  return(1);
  }
