/*--- Chippie ---*/

#strict
#include _KI_

local countdown;

/* Initialisierung */

protected Initialize:
  Refit();
  SetAction("Flight");
  ChangeDir();
  return(1);

/* Einwirkungen */

CatchBlow:
  return(CheckHurt());

Damage:
  return(CheckHurt());

CheckHurt:
  if(GetEnergy()<=GetPhysical("Energy")/2000)
    SetAction("Hurt");
  return(1);

protected Death:
  RemoveObject();
  ObjectCall(CreateObject(EXPL),"Launch",30*GetCon()/100);
  return(1);

/* Aktivität */

protected Activity:
  _inherited();
  if(GetAction() eq "Frozen") return(1);
  if(GetAction() eq "Hurt") return(1);
  // Richtung ändern
  if(!Local(2))
    if (Not(Random(10))) ChangeDir();
  // Fertig
  if(Local(2)) {
    if(Contained(Local(2)))
      Reset();
    if(GetID(Local(2))!=_FFD) {
      if(!GetAlive(Local(2))) Reset();
      if(!Visible(GetOwner(),Local(2))) Reset();
      if(!PathFree( GetX(),GetY(),GetX(Local(2)),GetY(Local(2)) )) Reset();
    }
  }
 return(1);

Reset:
  Local(2)=0;
  ChangeDir();
  return(1);

Fly:
  // Feinde angreifen
  Local(2)=FindTarget(-100,-75,200,150);
  // Falls hinter einen Force Field
  /*if(!Local(2))
    if(Var(0)=FindObject(_FFD,-75,-50,150,100,9,0,0,NoContainer()))
      if(Visible(GetOwner(),Var(0)))
        Local(2)=Var(0);*/
  if(!Local(2))
    return(1);
  Attack(Local(2));
  if(Distance(GetX(),GetY(),GetX(Local(2)),GetY(Local(2)))<=30)
    countdown++;
  else
    countdown=0;
  SetClrModulation(RGB(255,255-countdown*255/5,255-countdown*255/5));
  if(countdown>=5)
    Death();
  return(1);

/* Aktionen */

Attack:
  var speed = 20*GetCon()/100;
  // Ziel anpeilen
  SetR( Angle(GetX(),GetY(),GetX(Par(0)),GetY(Par(0))) );
  // Geschwindigkeitskontrolle  
  SetXDir(GetXDir() * 3 / 4 + Sin(GetR(),speed) * 1 / 4);
  SetYDir(GetYDir() * 3 / 4 - Cos(GetR(),speed) * 1 / 4);
  return(1);

ChangeDir:
  Var(0)=Random(360);
  SetXDir(Sin(Var(0),Random(20)));
  SetYDir(-Cos(Var(0),Random(20)));
  if(Random(2))
    return(1);
  SetXDir();
  SetYDir();
  return(1);

ContactLeft:
  SetXDir(GetXDir()*-1);
  if(Random(2))
    ChangeDir();
  return(1);

ContactRight:
  SetXDir(GetXDir()*-1);
  if(Random(2))
    ChangeDir();
  return(1);

ContactBottom:
  SetYDir(GetYDir()*-1);
  if(Random(2))
    ChangeDir();
  return(1);

ContactTop:
  SetYDir(GetYDir()*-1);
  if(Random(2))
    ChangeDir();
  return(1);

/* Fortpflanzung */

public Reproduction:
 return(1);

/* Eingefroren */
Frozen: 
  if(OnFire(this())) Extinguish(); // Nötigenfalls löschen
 return(1);