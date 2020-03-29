#strict

Initialize:
  SetAction("Los");
  return(1);

Test:
  if(SetLocal(1,FindObject(0,-50,-50,100,100,OCF_CrewMember()))) SetAction("AbdiePost");
  return(1);

Erstellen:
  SetLocal(1,1,FindObject(_GS1,0,0,-1,-1));
  return(1);