#strict

Initialize:
SetAction("Implode");
return(1);


Bumm:
Sound("Boom");
return(1);

Resize:
  DoCon(100);
  SetVar(0,Div(GetCon(),10));	// Durchmesser
  while (SetVar(1,FindObject(0,Div(Var(0),-2),Div(Var(0),-2),Var(0),Var(0),OCF_Living(),0,0,NoContainer(),Var(1))))
      LivingInRange(Div(Var(0),2),Var(1));
  if (Equal(GetCon(),8000))	// Maximale Größe der Shockwave
    return(RemoveObject(this()));
  return(1);

LivingInRange:		// Par(0): Radius; Par(1): C4OBJ Living
  // Lebensenergie je nach Entfernung vom Mittelpunkt abziehen
  // (-radius+Objectdistance-10)/20
  DoEnergy( Div(Sum(Mul(Par(0),-1),ObjectDistance(Par(1)),-10),20) , Par(1) );
  DoEnergy(-1,Par(1));	// Auch bei einfacher Berührung
  // kleine Schleudereinlage: xspd=r-DeltaY; yspd=r-DeltaX
  Fling( Par(1),
         Div( Sub(GetX(Par(1)),GetX(this())) , Div(Par(0),7) ),
         Div( Sub(GetY(Par(1)),GetY(this())) , Div(Par(0),7) )
        );
  return(1);