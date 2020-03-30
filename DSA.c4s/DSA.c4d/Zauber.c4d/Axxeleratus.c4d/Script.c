Activate:
  SetAction("TuWirken");
  SetLocal(0,Par(0));
  SetPhysical("Walk",160000,2,Local(0));
  SetPhysical("Jump",25000,2,Local(0));
  SetPhysical("Scale",Mul(GetPhysical("Scale",0,Local(0)),3),2,Local(0));
  SetPhysical("Hangle",Mul(GetPhysical("Hangle",0,Local(0)),3),2,Local(0));
  SetPhysical("Swim",Mul(GetPhysical("Swim",0,Local(0)),4),2,Local(0));
  SetPhysical("Dig",Mul(GetPhysical("Swim",0,Local(0)),2),2,Local(0));
  return(1);

TuNichtMehrWirken:
  ObjectCall(Local(0),"Redefine");
  RemoveObject();
  return(1);

AbleToCastByElf:
  return(1);

AbleToCastByMagier:
  return(1);