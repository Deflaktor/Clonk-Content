#strict
#include _POV

/* Wird abgefeuert, Par(0) ist Schußrichtung, Par(1) gibt an, Ob Schuß besonders schnell sein soll */
Launch:  
  if (Equal(Par(0),DIR_Left())) SetLocal(0,-30);
  if (Equal(Par(0),DIR_Right())) SetLocal(0,+30);
  SetAction("Travel");
  SetPhase(4);
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
  Sound("BOOM");
  return(1);

Resize:
  DoCon(100);
  SetVar(0,Div(GetCon(),10)); // Durchmesser
  while (SetVar(1,FindObject(0,Div(Var(0),-2),Div(Var(0),-2),Var(0),Var(0),OCF_Living(),0,0,NoContainer(),Var(1))))
      LivingInRange(Div(Var(0),2),Var(1));
  if (Equal(GetCon(),6000)) // Maximale Größe der Shockwave
    return(RemoveObject(this()));
  return(1);

LivingInRange:    // Par(0): Radius; Par(1): C4OBJ Living
  // Lebensenergie je nach Entfernung vom Mittelpunkt abziehen
  // (-radius+Objectdistance-10)/20
  DoEnergy( Div(Sum(Mul(Par(0),-1),ObjectDistance(Par(1)),-10),100) , Par(1) );
  DoEnergy(-2,Par(1));  // Auch bei einfacher Berührung
  // kleine Schleudereinlage: xspd=r-DeltaY; yspd=r-DeltaX
  Fling( Par(1),
         Div( Sub(GetX(Par(1)),GetX(this())) , Div(Par(0),7) ),
         Div( Sub(GetY(Par(1)),GetY(this())) , Div(Par(0),7) )
        );
  return(1);