#strict

Dangerous:
  while(SetVar(0,FindObject(0,-40,-40,80,80,OCF_Living(),0,0,NoContainer(),Var(0)))) Harm(Var(0));
  return(1);

Harm:
  DoEnergy( -Dmg() , Par(0) );
  DoDamage( Dmg()/2 , Par(0) );
  return(1);

Remove: 
  return(RemoveObject());

Dmg: return(2);