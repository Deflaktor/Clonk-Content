/*--- Chippie ---*/

#strict
#include _KI_

// Locals 0: Agression

local parent;

/* Initialisierung */

protected Initialize:
  Refit();
  SetAction("Walk");
  ChangeDir();
  return(1);

public Birth:
  Refit();
  SetAction("Walk");
  ChangeDir();
  parent=Par(0);
  SetCommand(this(), "Follow", parent, 0, 0, 0, 1);
  return(1);

/* Zustand */

private Aggression: 
  return(Local(0));

Rage:
  return(SetLocal(0,Local(0)+1));
  
/* Einwirkungen */

CatchBlow:
  _inherited(Par(0),Par(1));
  if(parent&&target) {
    parent->SetNemesis(target);
  }
  if(GetOwner(Par(1))!=-1)
    SetLocal(0,Sum(Local(0),+1));
  return(1);

Damage:
  _inherited(Par(0),Par(1));
  if(parent&&target) {
    ObjectCall(parent, "SetNemesis", 0, target);
  }
  SetLocal(0,Sum(Local(0),+1));
  return(1);

public SetNemesis:
  if(!PathFree(GetX(),GetY(),GetX(Par(1)),GetY(Par(1))))
    return(1);
  target=Par(1);
  SetLocal(0,1000);
  walkBonus=2;
  SetCommand(this(), "MoveTo", target, 0, 0, 0, 1);
  AppendCommand(this(), "Call", this(), Par(1),0,0,0, "SetNemesis");
  return(1);
  
protected Death:
  SetDir(0);
  ChangeDef(DCHP);
  SetAction("Dead");
 return(1);

/* Aktivität */

protected Activity:
  _inherited();
  if(GetAction() eq "Frozen") return(1);
  if(GetAction() eq "Hug")
    if (Not(GetAlive(GetActionTarget()))) SetAction("Walk");
  // Erwachsen geworden? 
  if(GetCon()==100&&parent||GetAction() S= "Hug") {
    SetCommand(this(), "None");
	parent=0;
  }
  // Richtung ändern
  if (Not(Random(25))) ChangeDir();
  // Fallenlassen
  if (Not(Random(25))) JumpDrop();
  // Feuer oder Wasser mögen wir nicht
  if (OnFire()||InLiquid()) 
    Frenzy();
  // Flüssigkeit kühlt ab
  if (InLiquid()&&Local(0)<1000)
    SetLocal(0,0);
  // Angesaugte Chippies wegschütteln
  if(Var(0)=FindObject(GetID(),-10,-10,20,20,0,"Hug",this(),NoContainer())) {
    JumpDrop();
    if(Random(2)) {
      Var(0)->SetAction("Walk");
      Fling(Var(0),Random(8)-4,-1-Random(3));
      Fling(this(),Random(8)-4,-1-Random(3));
    }
    return(1);
  }
  // Vor Feinden weglaufen
  if (Not(Aggression()))
    while(Var(0)=FindObject(0,-100,-100,200,200,OCF_Prey(),0,0,NoContainer(), Var(0)))
      if(GetTarget(Var(0)))
        if(PathFree(GetX(),GetY(),GetX(Var(0)),GetY(Var(0))))
          Escape(Var(0));
  // Erzfeind verfolgen
  Var(0)=GetCommand(0, 1);
  if (!Var(0))
    walkBonus=1;
  else
    walkBonus=2;
  // Feinde angreifen
  if (Aggression())
    while(Var(0)=FindObject(0,-75,-50,150,100,OCF_Prey(),0,0,NoContainer(), Var(0)))
      if(GetTarget(Var(0)))
        if(PathFree(GetX(),GetY(),GetX(Var(0)),GetY(Var(0))))
          JumpAt(Var(0));
  // Fortpflanzung
  if (!Random( (Global(5)+100)*Sqrt(ObjectCount(GetID())+1) ))
    Reproduction();
  // Fertig
 return(1);

/* Aktionen */

private Frenzy:
  if (SEqual(GetAction(),"Hug")) SetAction("Walk");
  SetComDir(Sum(1,Mul(Random(4),2)));
  if (Not(Random(5))) JumpDrop();
 return(1);

private JumpDrop:
  if (SEqual(GetAction(),"Hangle")) return(SetAction("Jump"));
  Jump();
 return(1);

private JumpAt:
  if (Not(GetAlive())) return(0);
  //target=Par(0);
  SetAction("JumpAt");
  SetXDir( Sub(GetX(Par(0)),GetX()) );
  SetYDir( Sub(GetY(Par(0)),GetY(),20) );
 return(1);

private JumpAtTravel:
  if(FindObject(GetID(),-10,-10,20,20,0,"Hug",this(),NoContainer())) return(1);
  while(SetVar(0,FindObject(0,+1,+1,0,0,OCF_Prey(),0,0,NoContainer(), Var(0))))
    if(GetTarget(Var(0)))
      if(GetID(Var(0))!=GetID()||Random(2))
        SetAction("Hug",Var(0));
  return(1);

private SuckHug:
  Sound("ChippieSuck");
  DoEnergy(Min(-3*KannTreten(GetActionTarget())/10,-1),GetActionTarget());
  DoDamage(Max(3*KannTreten(GetActionTarget())/10,1),GetActionTarget());
  if (!GetActionTarget()) SetAction("Walk");
  if (Not(GetAlive(GetActionTarget()))) SetAction("Walk");
 return(1);

private ChangeDir:
  if (SEqual(GetAction(),"Hangle")) return(ChgDirHangle());
  SetVar(0,COMD_Left());
  if (Random(2)) SetVar(0,COMD_Right());
  SetComDir(Var(0));
 return(1);

private Escape:
  if(SEqual(GetAction(),"Hangle")) return(EscapeHangle());
  SetVar(0,Sub(GetX(this()),GetX(Par(0))));
  if(GreaterThan(Var(0),0)) return(SetComDir(COMD_Right()));
  return(SetComDir(COMD_Left()));

private ChgDirHangle:
  SetVar(0,COMD_Up());
  if(Random(2)) SetVar(0,COMD_Down());
  SetComDir(Var(0));
 return(1);

private EscapeHangle:
  SetVar(0,Sub(GetY(this()),GetY(Par(0))));
  if(GreaterThan(Var(0),0)) return(SetComDir(COMD_Down()));
 return(SetComDir(COMD_Up()));

/* Fortpflanzung */

public Reproduction:
 if(GetCon()!=100)
   return(1);
 ObjectCall(CreateConstruction(GetID(this()),0,0,GetOwner(),30),"Birth", this());
 return(1);

/* Eingefroren */
Frozen: 
  SetXDir(0); // Bei Vereisung stehenbleiben
  if(OnFire(this())) Extinguish(); // Nötigenfalls löschen
 return(1);