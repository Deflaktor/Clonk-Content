#strict

Initialize:
  SetDir(BoundBy(
    GetWind()/10+4-GetXDir(GetActionTarget(0,GetActionTarget()))/5,
    0,8
  ));
  return(1);

CalculateManyStuff:
  var Tank = GetActionTarget();
  var TankR = GetR(Tank);

  Wind2Fly();

//17

  if( GetID(Tank) == PM7K )
    SetVertexXY(0,-Sin(TankR - 24,17)-1,Cos(TankR - 24,17)+5);

  if( GetID(Tank) == PN7K )
    SetVertexXY(0,-Sin(TankR + 24,17)-1,Cos(TankR + 24,17)+5);

  return(1);

Wind2Fly:  
  var Wind = GetWind()/10+4-GetXDir(GetActionTarget(0,GetActionTarget()))/5;

  if( Wind > GetDir() )
    SetDir(BoundBy(
      GetDir() + 1 ,
      0,8
    ));

  if( Wind < GetDir() )
    SetDir(BoundBy(
      GetDir() - 1 ,
      0,8
    ));

  return(1);

SetVertexXY: // Nr, X/KEEP, Y/KEEP, [Objekt]
  var VertexNr = Par(0);
  var VertexX = Par(1);
  var VertexY = Par(2);
  var obj = Par(3);

  if ( !obj ) obj = this() ;

  if (!( VertexX == KEEP ))
    SetVertex(VertexNr,0,VertexX,obj);

  if (!( VertexY == KEEP ))
    SetVertex(VertexNr,1,VertexY,obj);

  return(1);
