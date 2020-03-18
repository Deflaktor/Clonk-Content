#strict
#appendto CHEM

private func DoorClosed() {
  for(var i=0,pContent; pContent=Contents(i); ++i)
    if(DefinitionCall(GetID(pContent),"IsLorry")||GetID(pContent)==ALC_)
      GrabContents(pContent);
  return(1);
}

Collection:
  DoorClosed();
  return(1);