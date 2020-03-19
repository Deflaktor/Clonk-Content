/*-- Waypoint --*/

#strict

Initialize:
  SetAction("ShowWaypoint");
  return(1);

IsWaypoint:
  return(1);

NextWaypointID:
  return(WAY2);

NextWaypoint:
  return(FindObject(NextWaypointID(),0,0,-1,-1));

DropWaypoint:
  return(CreateObject(NextWaypointID()));

HideAllWaypoints:
  SetAction("Waypoint");
  while(Var(0)=FindObject(0,0,0,0,0,0,0,0,0,Var(0)))
    if(ObjectCall(Var(0),"IsWaypoint"))
      ObjectSetAction(Var(0),"Waypoint");
  return(1);

ShowAllWaypoints:
  SetAction("ShowWaypoint");
  while(Var(0)=FindObject(0,0,0,0,0,0,0,0,0,Var(0)))
    if(ObjectCall(Var(0),"IsWaypoint"))
      ObjectSetAction(Var(0),"ShowWaypoint");
  return(1);