Initialize:
  return(1);

Gift:
  //Local(0) = Ziel
  SetLocal(1,Par(0));  //Dauer speichern
  SetLocal(2,Par(1));  //Schaden speichern
  SetAction("giftigifti");
  return(1);

damage:
  SetLocal(9,Sum(Local(9),1));
  if(GreaterThan(Local(9),Local(1))) Call("finito");
  Punch(Local(0),Local(2));
  return(1);


finito:
  RemoveObject();
  return(1);