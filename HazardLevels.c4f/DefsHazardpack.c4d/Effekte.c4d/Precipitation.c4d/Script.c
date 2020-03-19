#strict

Precipitation:
  if (Random(50)>Local(2)) return(0);
  Var(0)=Local(0);
  if (GetTemperature()<0)
  if (Var(0)==Material("Water")) Var(0)=Material("Snow");

  InsertMaterial(Var(0), ((GetX()+Random(Local(1)))%LandscapeWidth())-GetX(),-GetY());
  InsertMaterial(Var(0), ((GetX()+Random(Local(1)))%LandscapeWidth())-GetX(),-GetY());
  InsertMaterial(Var(0), ((GetX()+Random(Local(1)))%LandscapeWidth())-GetX(),-GetY());

  return(1);

Movement:
  SetXDir( BoundBy( GetWind(0,3), -100, 100 ) );
  if (GetX()>LandscapeWidth()-20) SetPosition(25,-1);
  if (GetX()<20) SetPosition(LandscapeWidth()-25,-1);
  return(1);

Activate:
  SetAction("Process");
  Local(0)=Par(0); Local(1)=Par(1); Local(2)=Par(2);
  return(1);
