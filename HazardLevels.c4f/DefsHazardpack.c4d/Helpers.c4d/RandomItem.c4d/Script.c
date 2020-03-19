/*-- Neues Objekt --*/

#strict
local sumPrice, maxPrice, minPrice;

protected Initialize:
  minPrice = 10000;
  return(1);

AddAllExceptDatacubesAndWeapons:
  AddItems();
  AddAmmoPackages();
  AddBatteries();
  AddMineGrenadePackages();
  return(1);

AddItems:
  Add(_MED);
  Add(_POW);
  return(1);

AddDatacubes:
  Add(_DC1);
  Add(_DC2);
  Add(_DC3);
  return(1);

AddWeapons:
  Add(_RMT);
  Add(_FFG);
  Add(_BLZ);
  Add(_WP7);
  Add(RWP1);
  Add(DR1D);
  Add(_EGW);
  Add(_WP3);
  Add(_WP5);
  Add(GB01);
  Add(_HLR);
  Add(HLS_);
  Add(_WP0);
  Add(_WLG);
  Add(_WP6);
  Add(_WMW);
  Add(MINI);
  Add(RWP2);
  Add(_WP1);
  Add(_WP8);
  Add(_PR4);
  Add(_WP2);
  Add(_SLG);
  Add(_PR3);
  Add(_SG1);
  Add(_WP9);
  Add(GB02);
  return(1);

AddAmmoPackages:
  Add(_AP7);
  Add(RAP1);
  Add(_AP3);
  Add(_HLA);
  Add(_PP6);
  Add(_SLA); // Schleim-Pack
  Add(_AP9); // Shrinker-Pack
  // Rockets
  Add(_ARP); // Atom-Raketen-Pack
  Add(_HMP); // Homing-Raketen-Pack
  Add(_AP2); // 
  Add(_SR4);
  Add(_RP2);
  Add(_SR2);
  return(1);

AddSuperWeapons:
  Add(_KUT);
  Add(_QRD);
  Add(_SWE);
  return(1);

AddBatteries:
  Add(_CEL);
  Add(RAP2);
  Add(_AP0);
  return(1);

AddMineGrenadePackages:
  Add(_FMP);
  Add(_EMP);
  Add(_AP8);
  Add(SWMP);
  Add(_CGP);
  Add(_AP5);
  return(1);

Get:
  SetVar(0,Random(sumPrice));
  var i,id,price;
  while(id = GetComponent(0, i++)) {
    price = minPrice+maxPrice-GetComponent(id);
    if(Var(0)<price)
      return(DoublePrice(id));
    Var(0) -= price;
  }
  return(0);

DoublePrice:
  Var(0) = GetComponent(Par(0));
  Var(1) = Var(0) * 2;
  SetComponent(Par(0),Var(1));
  if(Var(1)>maxPrice)
    maxPrice = Var(1);
  if(Var(0)==minPrice)
    minPrice = Var(1);
  sumPrice += Var(1) - Var(0);
  return(Par(0));

IncreasePrice:
  Var(0) = GetComponent(Par(0));
  Var(1) = Var(0) + 1;
  SetComponent(Par(0),Var(1));
  if(Var(1)>maxPrice)
    maxPrice = Var(1);
  if(Var(0)==minPrice)
    minPrice = Var(1);
  sumPrice += Var(1) - Var(0);
  return(Par(0));

Add:
  if(GetComponent(Par(0)))
    return(-1);
  SetVar(0,GetValue(0,Par(0)));
  SetComponent(Par(0),Var(0));
  if(Var(0)>maxPrice)
    maxPrice = Var(0);
  if(Var(0)<minPrice)
    minPrice = Var(0);
  sumPrice += Var(0);
  return(Var(0));