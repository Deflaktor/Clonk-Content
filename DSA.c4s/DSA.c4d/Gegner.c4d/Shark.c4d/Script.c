/*-- Hai --*/

#strict

/* Initialisierung */

protected Initialize:
  SetAction("Swim");
  SetComDir(COMD_Left());
  if (Random(2)) SetComDir(COMD_Right());
  return(1);

/* Aktivit‰t */

private Swimming:
  if (Var(0)=FindObject(0, -20+40*GetDir()-20,-20,-20+40*GetDir()+40,40, OCF_Prey()))
    if (SEqual(GetAction(Var(0)),"Swim"))
      if (GetAlive(Var(0)))
        if (!Contained(Var(0)))
          Attack(Var(0));
  return(1);

/* TimerCall */

private Activity: 
  // Nichts machen
  if (Random(2)) return(1);
  // Befehle vergessen  
  SetCommand(this(),"None");
  // Nur wenn der Hai schwimmt
  if (GetAction()ne"Swim") return(1);
  // Beute suchen und verfolgen
  if (Var(0)=FindObject(0, -500,-200,1000,400, OCF_Prey(), "Swim"))
    SetCommand(this(),"Follow",Var(0));
  // Zuf‰llig wenden
  if (Random(2)) return(TurnRight(),SetComDir(COMD_Right()));
  return(TurnLeft(),SetComDir(COMD_Left()));

/* Aktionen von auﬂerhalb */

public Eat:
  ObjectCall(Par(0),"Feed",100);
  RemoveObject();
  return(1);
  
public Kill:
  DoEnergy(-100);
  return(0);
 
/*public Cook:
	ChangeDef(CSHK);
	return(1);*/

/* Kontakt */

protected ContactLeft:
  return(TurnRight());
  
protected ContactRight:
  return(TurnLeft());

protected ContactTop:
  SetComDir(COMD_Down());
  return(1);

protected ContactBottom:
  if (GetAction()ne"Walk") SetComDir(COMD_Up());
  if (Random(10)) SetComDir(COMD_Right());
  if (Random(10)) SetComDir(COMD_Left());
  return(1);

/* Bewegung */

private TurnRight:
  if (Stuck()) return(0);
  if (GetDir()!=DIR_Right()) SetAction("Turn");
  SetXDir(0);
  SetDir(DIR_Right());
  if (GetComDir()==COMD_Left()) 
    SetComDir(COMD_Right()); 
  return(1);

private TurnLeft:
  if (Stuck()) return(0);
  if (GetDir()!=DIR_Left()) SetAction("Turn");
  SetXDir(0);
  SetDir(DIR_Left());
  if (GetComDir()==COMD_Right()) 
    SetComDir(COMD_Left()); 
  return(1);

/* Aktionen */

private Attack:
  SetAction("Jaw");
  Sound("Munch1");
  Punch(Par(0),16);
  return(1);

protected Death:
  SetDir(0);
  ChangeDef(DSHK);
  SetAction("Dead");
  return(1);

public Reproduction:
  if (GetAction() ne "Swim") return(0);
  Var(0)=CreateConstruction(GetID(this()),0,0,-1,40);
  ObjectCall(Var(0),"Birth");
  return(1);

public Birth:
  SetAction("Swim");
  SetComDir(COMD_Left());
  if (Random(2)) SetComDir(COMD_Right());
  return(1);
