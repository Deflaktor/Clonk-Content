#strict
#include _POV

/* Wird abgefeuert, Par(0) ist Schußrichtung, Par(1) gibt an, Ob Schuß besonders schnell sein soll */
Launch:  
  if (Equal(Par(0),DIR_Left())) SetLocal(0,-30);
  if (Equal(Par(0),DIR_Right())) SetLocal(0,+30);
  SetAction("Travel");
  SetPhase(4);
  SetLocal(2,CreateObject(SLRO,0,0,-1));
  ObjectCall(Local(2), "Connect",this(),Par(2));
  return(1);
  
/* Fliegt */
Travel:
  // Treffer-Überprüfung
  if(CheckHit(-5,-5,10,10))
    return(Hit());
  if(GBackSolid()) return(Hit());
  // Bewegung
  SetXDir(Local(0));
  SetYDir(0);
  // Je nach Phase kommt Flare
  if(Equal(GetPhase(),5)) // Phase 0
    CreateObject(_FLR,0,0,-1);
  if(Or(Equal(GetPhase(),1),Equal(GetPhase(),4))) // Phase 1 oder 4
    And(CreateObject(_FLR,0,-2,-1),CreateObject(_FLR,0,+2,-1));
  if(Or(Equal(GetPhase(),2),Equal(GetPhase(),3))) // Phase 2 oder 3
    And(CreateObject(_FLR,0,-3,-1),CreateObject(_FLR,0,+3,-1));
  return(1);
  
/* Treffer */
Hit:
  SetAction("Implode");
  //SetPosition(GetX()-Local(0),GetY());
  return(1);

Zap:
  if(!Local(2))
    RemoveObject();
  while(SetVar(0,FindObject(0,-200,-200,400,400,0,0,0,NoContainer(),Var(0))))
    if(Or(
          // Beim suchen wird diese Reihenfolge eingehalten. Soll heißen, wenn ein Clonk neben einem Panzer steht, wird zuerst der Clonk attackiert
          BitAnd(GetOCF(Var(0)),OCF_CrewMember()),
          BitAnd(GetOCF(Var(0)),OCF_Living()),
          Equal(GetID(Var(0)),_DRN)
          ))
      // Weg Frei
      if(PathFree(GetX(),GetY(),GetX(Var(0)),GetY(Var(0))))
      // Gehört nicht dem Spieler
      if(Not(Equal(GetOwner(Contained()), GetOwner(Var(0)) )) )
        // Lebt noch
        if(GetAlive(Var(0)))
          // Zappen!
          ObjectCall(CreateObject(HLRO,0,0,-1), "Launch",this(),Var(0),Local(2));
  return(1);