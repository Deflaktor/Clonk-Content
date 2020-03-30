Initialize:
  SetAction("Be");
  return(1);

Erstellen:
if(Equal(Local(1),1)) {
CreateObject(_S09);
RemoveObject();
return(1);
}
return(0);