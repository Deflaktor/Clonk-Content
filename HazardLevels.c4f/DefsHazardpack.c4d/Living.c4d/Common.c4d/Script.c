/*-- Neues Objekt --*/

#strict

local walkBonus;

protected func Activity() {
  if(!walkBonus)
    walkBonus=1;
  var percentMultiplicator = 100+(GetCon()-100)/2;
 /* RelativePhysical("Walk", percentMultiplicator * walkBonus, 2);
  RelativePhysical("Jump", percentMultiplicator, 2);
  RelativePhysical("Scale", percentMultiplicator, 2);
  RelativePhysical("Hangle", percentMultiplicator, 2);*/
}

// physicalName = Physical Name
// percentFactor = Percentage to change to from permanent value
// mode = Mode
private func RelativePhysical(string physicalName, int percentFactor, int mode) {
  if(GetPhysical(physicalName,1)==0)
    return(SetPhysical(physicalName,GetPhysical(physicalName,1,0,GetID()) * percentFactor/100, mode));
  else
    return(SetPhysical(physicalName,GetPhysical(physicalName,1) * percentFactor/100, mode));
  return(0);
}
 
protected func QueryCatchBlow(object obj) {
  if(ObjectCall(obj, "IsProjectile"))
    return(1);
  return(0);
}