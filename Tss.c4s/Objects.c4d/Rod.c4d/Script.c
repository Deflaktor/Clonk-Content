/*-- Zauberturm --*/

#strict


public func LightningStrike() 
{
  if(Local(0))
    ObjectCall(Local(0),"AddEnergy");
  return(1);
}

