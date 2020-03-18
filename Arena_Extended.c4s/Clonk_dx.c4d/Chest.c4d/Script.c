#strict

Activate:
  ObjectCall(Contained(),"MakeMenu");
  return(1);

//ruft der Clonk beim werfen auf, aber hier gibts den Befehl nicht
Check:
  return(1);

NoShiftOwner:
  return(1);