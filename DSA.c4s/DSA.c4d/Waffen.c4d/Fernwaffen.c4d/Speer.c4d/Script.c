/* -- Spear -- */

/* Werfen */
ControlThrow:
  if (Not(ObjectSetAction(Contained(),"ThrowSpear"))) return(0);
  return(1);
