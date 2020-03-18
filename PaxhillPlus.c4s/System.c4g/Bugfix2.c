/*-- Bugfix: Man kann viel Geld machen indem man einen Thron oder anderes Gebäude vor einer Heimatbasis baut,
             es hinein verschiebt und anschließend verkauft. --*/

#strict
#appendto OVEN
#appendto FRGE
#appendto FDRS
#appendto THRN
/*
RejectEntrance:
  return(1);
*/

CalcValue:
  return(30);
  
/*
SellTo:
  return(CNKT);
*/