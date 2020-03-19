// Local 0: XDir
// Local 1: YDir
// Local 2: Zeit bis Removen

#strict

Dmg: return(2*500/20);

/* Wird abgefeuert, Par(0) ist Schußrichtung */
Launch:  
  SetLocal(2,600+Random(400));
  SetAction("Travel");
  return(1);

Hit:
  Sound("Plumps");
  return(SetAction("CauseDamage"));

Dangerous:
  while(SetVar(0,FindObject(0,-80,-80,160,160,OCF_Living(),0,0,NoContainer(),Var(0)))) Harm(Var(0));
  if(GetActTime()>Local(2)) return(RemoveObject());
  return(1);

Harm:
  DoEnergy( (-80+ObjectDistance(Par(0)))/40 , Par(0) );
  return(1);

Damage: 
if(Par(0)>5)
  RemoveObject();
return(1);