/*-- Clonk DX --*/
#strict
#include CLON

local explodiert;

Schleuder:
  Message("Du hast bereits KamiKaze Etui!",this());
  Sound("Error");
  return(1);

Kaze:
  Message("Die hast du doch schon!",this());
  Sound("Error");
  return(1);

ControlSpecial2:
  //SetPlrView(GetOwner(),this());
  // KamiKaze Explode
  Boom();
  Kill();
  return(1);

Boom:
  if(explodiert&&!epicMode)
    return(0);
  Explode(70,CreateObject(FLNT,0,0,GetOwner()));
 // Explode(70,CreateObject(FLNT,0,0,GetOwner()));
 // SetVar(0,CreateObject(WP32,0,32));
 // SetOwner(GetOwner(this()),Var(0));
 // ObjectCall(Var(0),"Launch",70);
  explodiert = true;
  return(1);
  
Death:
  Boom();
  return(_inherited(Par(), Par(1)));