#strict
#include PRNT

Initialize:
  SetAction("SetColor");
  return(1);

SetMyColor:
  if(GetOwner()==-1)
    SetColorDw(RGBa(255, 255, 255, 0));
  return(1);

Shot:
  return(Check());
  
Check:
  Local(0) = 1;
  return(1);
  
CheckIt:
  if(!Local(0)) return(0);
  if(SetVar(0,FindObject(GetID(),-20,-20,40,40,OCF_HitSpeed1(),0,0,NoContainer()))) 
    if(Inside(GetXDir(Var(0))/5 + GetX(Var(0)),GetX()-20,GetX()+20))
	  if(Inside(GetYDir(Var(0))/5 + GetY(Var(0)),GetY()-20,GetY()+20))
	    if(GetSpeed()>5&&GetSpeed(Var(0))>5)
		  if(!GBackSolid(0,1)&&!(Var(0)->GBackSolid(0,1)))
            return(Fuse(Var(0)));
  if(GetSpeed()<5&&GBackSolid(0,1)) Local(0)=0;
  return(-1);
  
Fuse:
  CreateObject(BGBM,0,0,GetOwner());
  RemoveObject(Par(0));
  RemoveObject();
  return(1);
  
Hit:
  Sound("RockHit*");
  return(1);

NoShiftOwner:
  return(!(GetAction()S="Idle"));

Entrance:
  if(ActIdle())
    SetOwner(GetOwner(Par(0)),this());
  return(1);

Activate:
  if(GetAction() S= "Setting")
    DelBomb();
  else
    ActivateBomb();
  SetOwner(GetOwner(Par(0)));
  /*
  CreateMenu(BOOM,Par(0),this());
  AddMenuItem( "Bombe zünden", "ActivateBomb", BOM1, Par(0), 0, Par(0) );
  AddMenuItem( "Bombe entschärfen", "DelBomb", BOM5, Par(0), 0, Par(0) );
  AddMenuItem( "Bombe entfernen", "KillBomb", BOM4, Par(0), 0, Par(0) );*/
  return(1);

ActivateBomb:
  Sound("Fuse");
  SetAction("Setting");
  return(1);

DelBomb:
  Sound("Pshshsh");
  ChangeDef(WBOB);
  return(1);

KillBomb:
  RemoveObject();
  return(1);

Incineration:
  Boom();
  return(1);

Boom:
  Explode(50);
  return(1);

Spark:
  if(ObjectCount(_FXA)<50)
    CastObjects(_FXA,5,10);
  return(1);

Damage:
  if (GetAction() S= "Setting")
  return(1);
  SetAction("Setting");
  return(1);