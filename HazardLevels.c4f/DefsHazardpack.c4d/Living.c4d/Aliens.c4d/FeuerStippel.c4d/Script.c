#strict
#include _KI_

Initialize:
  Refit();
  SetAction("Walk");
  return(1);

Frisch:
  SetLocal(0,-300);
  return(1);

Activity:
  _inherited();
  if(GetAction() eq "Frozen") return(1);
  if (SetVar(0,FindObject(0,-50,-50,100,100,OCF_CrewMember(),0,0,NoContainer())))
    if (!GetVisibility(Var(0)))
      Angriff(Var(0));
  while (SetVar(0,FindObject(0,-50,-50,100,100,OCF_CrewMember(),0,0,NoContainer(),Var(0)))) 
    if (Not(Equal(GetID(Var(0)),ST5B)))  
      if (Not(Equal(GetID(Var(0)),SR5B))) 
        if (Not(Equal(GetID(Var(0)),FSTB))) 
          if (!GetVisibility(Var(0)))
              if (GetAlive(Var(0))) Angriff(Var(0));
  SetLocal(0,Sum(Local(0),1));
  if (Not(GreaterThan(Local(0),-200))) return(0);
  if (Not(GreaterThan(Local(0),-100))) return(SetLocal(0));
  if (Not(SEqual(GetAction(),"Walk")))   
    if (And(Equal(GetXDir(),0),Equal(GetYDir(),0))) 
      SetCommand(this(),"MoveTo",Local(1));
  if (Not(GreaterThan(Local(0),0)))    return(SFTSuche());
  return(Suche());

Laufen:
  if (Equal(GetDir(),DIR_Left()))  And(SetVertex(3,0,0,0),SetVertex(2,0,-4,0));
  if (Equal(GetDir(),DIR_Right())) And(SetVertex(2,0,0,0),SetVertex(3,0,3,0));
  SetVertex(1,1,5,0);
  return(1);

Klettern:
  if (Equal(GetComDir(),COMD_Down())) return(SetVertex(1,1,5,0));
  SetVertex(1,1,0,0);
  SetCommand(this(),"None");
  return(1);

SFTSuche:
  if (Not(SEqual(GetAction(),"Walk")))        return(0);
  if (SetVar(0,FindObject(FSTB,0,0,-1,-1)))
    if (Inside(ObjectDistance(Var(0),0),0,2)) return(Verteilen());
  SetLocal(1,FindObject(0,0,0,-1,-1,OCF_CrewMember()));
  SetCommand(this(),"MoveTo",Local(1));
  return(1);

Suche:
  while (SetVar(0,FindObject(FSTK,-500,-500,1000,1000,0,0,0,0,Var(0)))) 
    if (Not(GreaterThan(GetY(),GetY(Var(0))))) 
      if (ObjectCall(Var(0),"Frei")) SetLocal(1,Var(0));
  if (Not(Local(1)))                              return(Feuerkokon());
  if (SetVar(0,FindObject(FSTB,0,0,-1,-1)))
    if (Inside(ObjectDistance(Var(0),0),0,2))        return(Verteilen());
  SetVar(0,FindObject(FSTK,0,0,-1,-1));
  if (Not(SEqual(GetAction(),"Walk")))            return(0);
  if (Inside(ObjectDistance(Var(0),0),0,5))       return(Weiter());
  SetCommand(this(),"MoveTo",Local(1));
  if (Not(Inside(ObjectDistance(Local(1),0),0,100))) return(0); 
  if (Inside(ObjectDistance(Var(0),0),0,10))      return(Feuerkokon());     return(1);

Feuerkokon:
  if (Not(Frei())) return(0);
  SetLocal(0,-100);
  return(1);

Verteilen:
  if (Random(2)) return(SetComDir(COMD_Left()));
  return(SetComDir(COMD_Right()));

Weiter:
  if (Equal(GetDir(),DIR_Left()))  SetComDir(COMD_Left());
  if (Equal(GetDir(),DIR_Right())) SetComDir(COMD_Right());
  return(1);

Angriff:
  if (SEqual(GetAction(),"Flame"))                          return(0);
  if (Not(Frei()))                                            return(0);
  if (Not(PathFree(GetX(),GetY(),GetX(Par(0)),GetY(Par(0))))) return(0);  
  SetXDir(SetVar(0,Sub(GetX(Par(0)),GetX())));
  SetYDir(Sub(GetY(Par(0)),GetY(),10));
  SetAction("Flame",Par(0));
  SetLocal(2);
  Sound("STAngriff*");
  if (GreaterThan(Var(0))) return(SetDir(DIR_Right()));
  return(SetDir(DIR_Left()));

ContactLeft:
  if (SEqual(GetAction(),"Flame")) 
    if (Equal(GetPhase(),17)) SetAction("Scale");
  return(1);
  
ContactRight:
  if (SEqual(GetAction(),"Flame")) 
    if (Equal(GetPhase(),17)) SetAction("Scale");
  return(1);

ContactBottom:
  if (SEqual(GetAction(),"Flame")) 
    if (Equal(GetPhase(),17)) SetAction("Walk");
  return(1);

Death:
  CastObjects(FSTF,20,50);
  Sound("STTot*");
  RemoveObject();
  return(1);

private Activity:
  // Nur im Gehen oder Schwimmen
  if (Not(Or( SEqual(GetAction(),"Walk"),SEqual(GetAction(),"Jump") ))) 
    return(1);
  // Feuer speien
  if (SEqual(GetAction(),"Walk"))
    if (Not(Random(8))) return(StartFlame());

private Flaming:
  Exit( CreateContents(DFLM), 
        Sum(-15,Mul(GetDir(),30)), +2, 0,
        Sum(-4,Mul(GetDir(),6),Random(2)),0);       
  if (GreaterThan(GetActTime(),10)) SetAction("Walk");
  return(0);

private StartFlame:
  SetAction("Flame");
  Sound("Inflame"); 
  return(0);

/* Steuerung */

protected ControlThrow:
  StartFlame();
  return(1);

Frei:
  return(Not(GBackSemiSolid()));

/* Eingefroren */
Frozen: 
  if(OnFire(this())) Extinguish(); // Nötigenfalls löschen
  return(1);