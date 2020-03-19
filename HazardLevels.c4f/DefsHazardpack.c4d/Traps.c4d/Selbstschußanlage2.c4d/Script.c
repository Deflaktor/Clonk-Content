/* Selbstschussanlage */

#strict

// Local(0) - potentielles Ziel
// Local(1) - Zustand - 1: Aktiviert 2: Deaktiviert
// Local(2) - Automatische Drehung aktiviert - 0:Nein 1:Ja

Initialize:
  SetLocal(1,1); // Aktivieren
  SetLocal(2,1); // Automatische Drehung aktivieren
  SetDir(Random(2));
  if(GetDir()) SetAction("ReadyRight");
  if(Not(GetDir())) SetAction("ReadyLeft");
  return(1);

Check:
  if(Equal(Local(1),0)) return(1);
  if(SEqual(GetAction(),"ShootLeft")) return(1);
  if(SEqual(GetAction(),"ShootRight")) return(1);
  if(SEqual(GetAction(),"LoadingLeft")) return(1);
  if(SEqual(GetAction(),"LoadingRight")) return(1);
  if(SetLocal(0,FindObject(0,-110,-10,107,30,OCF_Prey(),0,0,NoContainer()))) return(GoLeft());
  if(SetLocal(0,FindObject(0,3,-10,107,30,OCF_Prey(),0,0,NoContainer()))) return(GoRight());
  return(1);


GoLeft:
  if(SEqual(GetAction(),"ReadyRight")) if(Equal(Local(2),1)) SetAction("ReadyLeft");
  if(Not(SEqual(GetAction(),"ReadyLeft"))) return(1);
  if(Not(Local(0))) return(1);
  SetVar(1,CreateObject(_VL2,0,-5,GetOwner()));
  ObjectCall(Var(1),"Launch",DIR_Left());
  SetAction("LoadingLeft");
  return(1);

GoRight:
  if(SEqual(GetAction(),"ReadyLeft")) if(Equal(Local(2),1)) SetAction("ReadyRight");
  if(Not(SEqual(GetAction(),"ReadyRight"))) return(1);
  if(Not(Local(0))) return(1);
  SetVar(1,CreateObject(_VL2,0,-5,GetOwner()));
  ObjectCall(Var(1),"Launch",DIR_Right());
  SetAction("LoadingRight");
  return(1);

Aktivieren:
  SetLocal(1,1);
  SetAction("ReadyLeft");
  return(1);

Deaktivieren:
  SetLocal(1,0);
  SetAction("Deactivated");
  return(1);

Drehungaktivieren:
  SetLocal(2,1);
  return(1);

Drehungdeaktivieren:
  SetLocal(2,0);
  return(1);

Damage:
  if ( LessThan( GetDamage(), 45 ) ) return(0);
  SetAction("Destroyed");
  return(1);