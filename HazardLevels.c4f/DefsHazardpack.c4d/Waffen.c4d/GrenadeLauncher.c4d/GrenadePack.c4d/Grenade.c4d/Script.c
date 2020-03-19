/*-- Grenade --*/

#strict
#include _MOV

// Local 0 Timer (0 = BlowUp on Hit)

Initialize:
  return(1);

IsThrowWeapon:
  return(1);
  
Hit:
  Sound("MetalHit*");
  if(Local(0)==0) BlowUp();
  return(1);

TimerTick:
  Local(0)--;
  if (Local(0)==0) BlowUp();
  return(1);

Dmg: return(15);

BlowUp:
  ObjectCall(CreateObject(EXPL),"Launch",Dmg()+5);
  RemoveObject();
  return(1);

/* Aktivierung */
Activate:
  Sound("Bip");
  SetAction("Fuse");
  
  // Timer erhöhen
  if (Par(1)==0) Local(0)++;
  // Timer direkt setzen
  else SetLocal(0,Par(1));
  if (Local(0)>5) SetLocal(0,0);

  if (Local(0)!=0) {
    if (Par(0)) 
      Message("0%d",Par(0),Local(0));
  } else {
    SetAction("Idle");
    if (Par(0)) 
      Message("Explosion bei Aufprall",Par(0));
  }
  
  // Aktivator wird Besitzer
  SetOwner( GetOwner(Par(0)) );
  return(1);

/* Wird abgefeuert */
Launch:  
  // Scharfmachen
  if(Par(0)!=0)
    SetAction("Fuse");
  SetLocal(0,Par(0));
  // Sicht verfolgen
  SetPlrView(GetOwner(),this());
  return(1);