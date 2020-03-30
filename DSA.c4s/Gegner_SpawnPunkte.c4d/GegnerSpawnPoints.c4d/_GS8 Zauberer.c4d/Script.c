Initialize:
  SetAction("Be");
  return(1);

Erstellen:
if(Equal(Local(1),1)) {
CreateObject(ZPKI,0,0,-1);
SetLocal(1,0);
return(1);
}
return(0);