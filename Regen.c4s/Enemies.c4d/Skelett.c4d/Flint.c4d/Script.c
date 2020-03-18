#strict

Hit:
  if(!ActIdle())
    Explode(12);
  else 
    Sound("WoodHit*");
  return(1);
  
Departure:
  SetAction("Delay");
  return(1);
  
Shot:
  if(!Contained())
    SetAction("Checking");
  return(1);

Checkit:
  if(SetVar(0,FindObject(0,+1,0,0,0,OCF_Living()))) if(Not(Contained(Var(0)))) Hit();
  return(1);

/* Kann chemisch werden */
IsChemicalProduct: return(1);
