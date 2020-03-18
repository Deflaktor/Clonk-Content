#strict

#appendto WTWR

protected ActivateEntrance:
  if (!GetOwner()) SetOwner(GetOwner(Par()));
  return(_inherited(Par(), Par(1)));
