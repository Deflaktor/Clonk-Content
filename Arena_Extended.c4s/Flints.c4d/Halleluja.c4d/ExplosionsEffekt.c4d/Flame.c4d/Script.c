/*-- Neues Objekt --*/

#strict

Initialize:
  SetComDir(Random(2));
  SetAction("Blast");
  SetPhase(Random(10));
  return(1);

Smoke:
  if(GetActTime()>15 && !Random(3) && GetActTime()%2==0)
    ObjectCall(CreateObject(KACD), "Set", 100-50*GetPhase()/32);
  return(1);

Remove:
  RemoveObject();
  return(1);