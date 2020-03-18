
#strict
#include PRNT

Hit:
  Explode(20);
  return(1);

Check:
  SetAction("Delay");
  return(1);

Checkit:
  if(SetVar(0,FindObject(0,+13,+13,-26,-26,OCF_Living()))) if(Not(Contained(Var(0)))) Hit();
  return(1);
