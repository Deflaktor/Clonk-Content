/*-- Splitter --*/

#strict

protected Hit:
 ObjectCall(CreateObject(EXPL),"Launch",Dmg()*2);
 RemoveObject();
return(1);

Decay:
  Hit();
 return(1);
 
Dmg: return(7);