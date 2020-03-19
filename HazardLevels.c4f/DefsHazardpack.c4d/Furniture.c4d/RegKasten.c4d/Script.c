#strict

Initialize:
  SetLocal(0,100);
   SetAction("Start");
  return(1);

Fulling:
  if(Local(0)<92) return(SetLocal(0,Sum(Local(0),8)));
  return(SetLocal(0,100));

ControlUp:
  SetVar(0,Par(0));
  if(!Local(0)) return(Message("Regenerationsstation ist leer.|Versuchen sie es später erneut!",this()));
  if(GetEnergy(Var(0))>=GetPhysical("Energy",0,Var(0))/1000) return(0);
  var restEnergy = GetPhysical("Energy",0,Var(0))/1000-GetEnergy(Var(0));
  var energyPlus = Min(Local(0),Min(restEnergy,10));
  DoEnergy(energyPlus,Var(0));
  if(!GameCall("EndlessRegenerate")) {
    Local(0)-=energyPlus;
    Message("%d %",this(),Local(0));
  }
  Sound("RegBust");
  return(1);

