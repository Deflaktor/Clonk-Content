Initialize:
  SetAction("Los");
  return(1);

Test:
  if(SetLocal(1,FindObject(0,-50,-50,100,100,OCF_CrewMember()))) SetAction("AbdiePost");
  if(Equal(Global(8),1)) Call("fertig");
  return(1);

Erstellen:
  SetGlobal(8,1);

  Message("Interessant. Dieser Monolith könnte noch wichtig sein, wir müssen unbedingt einen Magier fragen!",Local(1));         

  RemoveObject();
  return(1);

fertig:
  RemoveObject();
  return(1);