/*-- Explosionsdruckwelle --*/

#strict
local alpha; // Durchsichtigkeit
local explo_obj; // Explosionssteuerungsobjekt

/* Aktivierung */

public func Activate()
  {
  explo_obj = Par(0);
  SetCon(1);
  SetAction("Blow");
  return(1);
  }

/* Aufblähen */

private func BlowExec()
  {
  if(FindObject(SDS1))
    ObjectCall(FindObject(SDS1), "Remove");
  if(FindObject(SDS2))
    ObjectCall(FindObject(SDS2), "Remove");
  Rumble(0,0,LandscapeWidth(),LandscapeHeight(), 10, 100);
  if(alpha>=255) return(EndGame());
  if(alpha==15) Sound("PowerBomb", 1);
  //if(GetCon()<=100)
  //  {
    DoCon(+4);
    SetPosition(GetX(explo_obj),GetY(explo_obj));
  //  }
  // Langsam durchsichtig werden
  SetClrModulation(RGBa(255,255,255,alpha));
  alpha=BoundBy(alpha+1,0,255);
  if(alpha>=70)
    alpha=BoundBy(alpha+2,0,255);
  Remove();
  return(1);
  }

GetSaugRadius:
  return(1024*GetCon()/200);

Remove:
while(SetVar(1,FindObject(0,-GetSaugRadius(),-GetSaugRadius(),GetSaugRadius()*2,GetSaugRadius()*2,0,0,0,NoContainer(),Var(1)))) {
  //if (!( GetCategory(Var(1)) & C4D_StaticBack() )) {
    if (Distance(GetX(),GetY(),GetX(Var(1)),GetY(Var(1)))<GetSaugRadius()) {
      if(!ObjectCall(Var(1),"DestroyIt",GetOwner())) {
        if( GetCategory(Var(1)) & C4D_Living() ) {
          Kill( Var(1) );
        } else {
          RemoveObject(Var(1));
        }
      }
    }
  //}
}
return(1);

DestroyIt:
  return(1);

EndGame:
  CreateObject(EDGE);
  RemoveObject();
  return(1);