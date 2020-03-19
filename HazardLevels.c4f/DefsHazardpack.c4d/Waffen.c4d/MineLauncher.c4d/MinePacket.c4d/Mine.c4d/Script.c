#strict

Dmg:
  return(30);

Hit:
  SetAction("Activated");
  Sound("Bip");
  return(1);
Check:
  // Kontakt-Überprüfung
  if(Var(0)=FindAOETarget(-10,-10,20,20)) {
	BlowUp(Var(0));
  }
  return(1);
  
BlowUp:
  ObjectCall(CreateObject(EXPL),"Launch",Dmg());
  RemoveObject();
  return(1);

IsThrowWeapon:
  return(1);