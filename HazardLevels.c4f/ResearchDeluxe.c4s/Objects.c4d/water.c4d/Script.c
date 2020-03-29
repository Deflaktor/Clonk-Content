#strict

Initialize:
  return(1);

Wasser:
 if(GameCall("MainEnergySupply")||Local(0))
   if(GetMaterial()!=Material("Water"))
     CastPXS("Water",300,10,0,0);
 return(1);


