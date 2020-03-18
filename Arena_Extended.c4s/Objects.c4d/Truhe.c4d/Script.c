#strict

Initialize:
  SetPosition(LandscapeWidth()/2,0);
  SetAction("Initialize");
  return(1);

Initialized:
  // Andere Objekte des gleichen Typs entfernen
  while(Var(1)=FindObject(GetID()))
    RemoveObject(Var(1));
  // Steuerungsaktion
  ObjectCall(CreateObject(_PUA,0,-17),"Attach",this());
  SetAction("Zu");
  return(1);

ControlDig:
  if(SEqual(GetAction(),"Offen")) Inventar(Par(0));
  return(1);

Inventar:
  Var(0)=CreateContents(GameCall("Zufallsflint2"),Par(0));
  SetOwner(GetOwner(Par(0)),Var(0));
  SetAction("Zu");
  return(1);

Destroy:
SetPosition(LandscapeWidth()/2,0);
return(1);

Test:
if (And(Equal(GetMaterial(0,-5),Material("Earth")),And(Equal(GetMaterial(0,-10),Material("Earth")),Equal(GetMaterial(0,0),Material("Earth")))))
  SetPosition(GetX(),0);
if (And(Equal(GetMaterial(0,-5),Material("Water")),And(Equal(GetMaterial(0,-10),Material("Water")),Equal(GetMaterial(0,0),Material("Water")))))
  SetPosition(GetX(),0);
if(GetAction() S= "Zu")
  SetLocal(0,Local(0)+1);
if(Local(0)>100) {
  SetLocal(0);
  SetAction("Offen");
}
return(1);