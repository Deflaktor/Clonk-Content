/*-- Half Explode --*/

#strict

Initialize:
 SetPosition();
 Global(0)=3;
 return(1);

Check:
  SetLocal(3,Sum(Local(3),1));
  if (Local(3)>15) {
    Global(0)=0;
    return(RemoveObject());
  }
  return(1);
