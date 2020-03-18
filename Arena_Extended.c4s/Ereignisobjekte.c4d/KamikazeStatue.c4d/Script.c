/*-- Tür --*/

Initialize:
  SetOwner(-1);
  return(1);

Incineration:
  Extinguish();
  return(1);

Hit:
  PutSolidMask();
  return(1);

PutSolidMask:
  SetSolidMask(0,0,28,38);
  return(1);
        
Damage:
  if ( LessThan( GetDamage(), 70 ) ) return(0);
  if (GetAction() S= "Idle") SetAction("Delay");
  return(1);

Blast:
  for(var i = 0; i<20; i++) {
    SetVar(0,CreateObject(KIK1,0,-20));
    ObjectSetAction(Var(0),"Tumble");
    Fling(Var(0),Sub(Random(100),50),Sub(Random(100),100));
  }
  CastObjects(_DF1,3,20,0,-5);
  RemoveObject();  
  Sound("Discharge");
  Sound("Blast2");
  return(1);

Destroy:
SetWealth(Par(0),GetWealth(Par(0))+100);
/*while(SetVar(1,FindObject(SDCL,0,0,0,0,0,0,0,0,Var(1))))
  if(GetOwner(Var(1))==Par(0)) {
    SetLocal(0,Local(0,Var(1))+10,Var(1));
    SetLocal(1);
  }*/
return(0);