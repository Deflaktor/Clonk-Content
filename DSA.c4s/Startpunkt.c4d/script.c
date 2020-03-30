Initialize:
  return(1);

ControlDig:
  CreateMenu(_STP);
  AddMenuItem("Als Magier spielen", "Go", MA3A );
  AddMenuItem("Als Krieger spielen", "Go", KR3A );
  AddMenuItem("Als Waldläufer spielen", "Go", WL3A );
 return(1);

Go:
  SetVar(0,CreateObject(Par(0)));
  GameCall("Relaunch",GetOwner(),Var(0));
  RemoveObject();
 return(1);


