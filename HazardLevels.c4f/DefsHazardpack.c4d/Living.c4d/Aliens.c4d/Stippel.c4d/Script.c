#strict
#include _KI_

/* Initialisierung */

public Redefine:
  ChangeDef(Par(0));
  SetAction("Walk");
  return(1);

public Frisch:
  SetAction("Walk");
  ChangeDir();
  return(1);

Platzen:
  return(Death());

/* Aktivität */

protected Activity:
  _inherited();
  if (GetAction() eq "Frozen")
    return(1);
  if (SEqual(GetAction(),"Beissen")) SetAction("Walk");
  // Feinde verfolgen
  if(Not(GetAlive(target))) SetCommand(this(),"None");
  if(Not(target)) SetCommand(this(),"None");
  if(ObjectDistance(target)>=600) SetCommand(this(),"None");
  if(!target) while(Var(0)=GetTarget(FindObject(0,-300,-50,600,100,OCF_Alive(),0,0,NoContainer(), Var(0)))) target=Var(0);
  if(!PathFree(GetX(),GetY(),GetX(target),GetY(target)-1)) target=0;
  if(target) SetCommand(this(),"Follow",target);
  // Feinde angreifen
  if (!SEqual(GetAction(),"Beissen"))
    while(Var(0)=FindObject(0,-75,-50,150,100,OCF_Alive(),0,0,NoContainer(),Var(0))) 
      if(GetTarget(Var(0)))
        if(PathFree(GetX(),GetY(),GetX(Var(0)),GetY(Var(0))))
          Angriff(Var(0));
  // Richtung ändern
  if (Not(Random(15))) ChangeDir();
  // Fallenlassen
  if (Not(Random(40))) JumpDrop();
  //An die Decke springen
  if (Not(Random(15))) Jump();
  // Feuer oder Wasser mögen wir nicht
  if (Or(OnFire(),InLiquid())) 
    Frenzy();
  // Fortpflanzung
  if (!Random( (Global(5)+100)*(ObjectCount(GetID())+1) ))
    Reproduction();
  // Fertig
  return(1);

/* Aktionen */

private Frenzy:
  SetAction("Walk");
  SetComDir(Sum(1,Mul(Random(4),2)));
  if (Not(Random(5))) JumpDrop();
  return(1);

private JumpDrop:
  if (SEqual(GetAction(),"Hangle")) return(SetAction("Jump"));
  Jump();
  return(1);

private ChangeDir:
  if (SEqual(GetAction(),"Hangle")) return(ChgDirHangle());
  if (SEqual(GetAction(),"Scale")) return(ChgDirScale());
  SetVar(0,COMD_Left());
  if (Random(2)) SetVar(0,COMD_Right());
  SetComDir(Var(0));
  SetAction("Walk");
  return(1);

private ChgDirHangle:
  SetVar(0,COMD_Left());
  if(Random(2)) SetVar(0,COMD_Right());
  SetComDir(Var(0));
  return(1);

private ChgDirScale:
  SetVar(0,COMD_Up());
  if(Random(2)) SetVar(0,COMD_Down());
  SetComDir(Var(0));
  return(1);


Angriff:
  SetXDir(SetVar(0,Sub(GetX(Par(0)),GetX())));
  SetYDir(Sub(GetY(Par(0)),GetY(),10));
  SetAction("Beissen",Par(0));
  SetLocal(0);
  Sound("STAngriff*");
  if (GreaterThan(Var(0))) return(SetDir(DIR_Right()));
  return(SetDir(DIR_Left()));

Beissen:
  SetLocal(0,Sum(Local(0),1));
  if (GreaterThan(Local(0),10))                             return(0);
  if (Not(GetAlive(GetActionTarget())))                     return(0);
  if (Contained(GetActionTarget()))                         return(0);
  if (Not(Inside(ObjectDistance(GetActionTarget(),0),0,5))) return(0);
  SetXDir(0);
  SetYDir(0);
  DoEnergy(-1*GetCon()/100,GetActionTarget());
  DoDamage(1*GetCon()/100,GetActionTarget());
  if (Equal(GetDir(),DIR_Left())) SetVar(0,-1);
  if (Equal(GetDir(),DIR_Right())) SetVar(0,+1);
  if (GetCon()>50)
  Fling(GetActionTarget(),Mul(Var(0),2),-1);
  return(1);

Incineration:
  return(Death()); 

Death:
  CastObjects(FZ5B,10,50);
  Sound("STTot*");
  RemoveObject();
  return(1);

Frei:
  return(Not(GBackSemiSolid()));


/* Fortpflanzung */

public Reproduction:
  if (Not(Frei())) return(0);
  CreateObject(SK5B,0,6);
  Sound("STGeburt*");
  return(1);

Plafontippel:
  if (Not(Frei())) return(0);
  CreateObject(_PLT,0,29);
  Sound("STGeburt");
  return(RemoveObject());

/* Eingefroren */
Frozen: 
  if(OnFire(this())) Extinguish(); // Nötigenfalls löschen
  return(1);