/*-- Neues Script --*/

#strict
#appendto _CPL

public func Activate(object clnk) {
  if(plan_id==OVEN)
    knowsOven=true;
  if(plan_id==DYNM)
    knowsDynamo=true;
  if(plan_id==WTWR)
    knowsWizard=true;
  if(plan_id==CST1)
    knowsSmallCastle=true;
  if(plan_id==CST2)
    knowsCastle=true;
  if(plan_id==ALTR)
    knowsAltar=true;
  return(_inherited());
}
