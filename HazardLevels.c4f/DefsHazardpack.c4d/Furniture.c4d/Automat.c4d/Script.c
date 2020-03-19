#strict

Completion:
  SetAction("Ham");
  return(1);

Damage:
  if(LessThan(50,GetDamage())) SetAction("Kaput");
  return(1);

ControlUp:
  if(!CheckEnergy()) return(And( Sound("Error"), Message("Nicht genug Energie.",this()) ));
  SetLocal(5,Par());
  if(Local(GetOwner(Local(5)))>5) return(And( Sound("Error"), Message("Der Automat ist leer.",this()) ));
  CreateMenu(GetID(),Local(5),this(),0,0,0,0,1);
  AddMenuItem("Cola mit Eiswürfeln","Cola",CL3V,Local(5),0,Local(5));
  AddMenuItem("Pommes","Pommes",PO3V,Local(5),0,Local(5));
  AddMenuItem("Hamburger","Burger",HB3V,Local(5),0,Local(5));
  return(1);

Cola:
  if(Local(GetOwner(Local(5)))>5) return(And( Sound("Error"), Message("Der Automat ist leer.",this()) ));
  SetLocal(GetOwner(Par(1)),Local(GetOwner(Par(1)))+1);
  CreateObject(CL3V,12,15);
  return(1);

Pommes:
  if(Local(GetOwner(Local(5)))>5) return(And( Sound("Error"), Message("Der Automat ist leer.",this()) ));
  CreateObject(PO3V,12,15);
  SetLocal(GetOwner(Par(1)),Local(GetOwner(Par(1)))+1);
  return(1);

Burger:
  if(Local(GetOwner(Local(5)))>5) return(And( Sound("Error"), Message("Der Automat ist leer.",this()) ));
  CreateObject(HB3V,12,15);
  SetLocal(GetOwner(Par(1)),Local(GetOwner(Par(1)))+1);
  return(1);

ChangeAction:
  if(Not(CheckEnergy()))
  return(SetAction("KeinStrom"));
  if(GetComponent(BLKD)) return();
  if(Not(Random(2))) return(SetAction("Ham"));
  return(SetAction("Pille1"));
 
Check:
  if(CheckEnergy())
  return(ChangeAction());
  return(0);

CheckEnergy:
if (Not(GameCall("MainEnergySupply", this()))) return(0);
return(1);
