#strict

local alpha;

Initialize:
SetAction("Implode");
alpha = 250;
SetClrModulation (RGBa(255, 255, 255, alpha), this());
return(1);

Bumm:
Sound("MOOB");
DoCon(3000);
return(1);

Resize:
  DoCon(-100);
  alpha -= 50;
  if(alpha<0)
    alpha=0;
  SetClrModulation (RGBa(255, 255, 255, alpha), this());
  SetVar(0,Div(GetCon(),10));	// Durchmesser
  while (SetVar(1,FindObject(0,Div(Var(0),-2),Div(Var(0),-2),Var(0),Var(0),OCF_Living(),0,0,NoContainer(),Var(1))))
      LivingInRange(Div(Var(0),2),Var(1));
  if (GetCon()<=100)	// Maximale Größe der Shockwave
    return(RemoveObject(this()));
  return(1);

LivingInRange:		// Par(0): Radius; Par(1): C4OBJ Living
  // Lebensenergie je nach Entfernung vom Mittelpunkt abziehen
  // (-radius+Objectdistance-10)/20
  DoEnergy( (Par(0)-ObjectDistance(Par(1))-10)/20 , Par(1) );
  DoEnergy(-2,Par(1));	// Auch bei einfacher Berührung
  // kleine Schleudereinlage: xspd=r-DeltaY; yspd=r-DeltaX
  SetVar(1,Sub(GetX(),GetX(Par(1))));
  SetVar(2,Sub(GetY(),GetY(Par(1))));
  // SetSpeed(Div(Var(1),2),Div(Var(2),2)-5,Par(0));
  
  Fling( Par(1),
         Div(Var(1),2),
         Div(Var(2),2)-5
        );
  return(1);