#strict

Damage:
  if(!Local(0))
    return(1);
  return(  ObjectCall(Local(0), "DamageRedirect", Par(0), Par(1), this()) );