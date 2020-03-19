/*-- HUD --*/

#strict

local owner;

Activate:
  owner = Par(0);
  SetOwner(GetOwner(Par(0)));
  SetVisibility(VIS_Owner());
  // Scroll with Viewport @see C4D_Parallax()
  SetLocal(0,0);
  SetLocal(1,0);
  SetPosition(Par(1),Par(2));
  SetAction("Phase");
  return(1);


Check:
  if(!owner)
    return(RemoveObject());
  if(GetID(owner)==HZCK||GetID(owner)==HCK2)
    RemoveObject();
  if(GetCursor(GetOwner())!=owner)
    RemoveObject();
  return(1);