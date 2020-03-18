
#strict

func IsAlchemContainer() { return(true); }

RejectEntrance:
  if(GetID(Par(0)) == CHEM ||GetID(Par(0)) == ALC_)
    return(false);
  if(GetOCF(Par(0)) & OCF_Living())
    return(false);
  return(true);

Departure:
  if(GetID(Par(0)) == ALC_)
    return(1);
  AddEffect("Reenter", Par(0), 200, 1, this(), 0, Par(0));
  return(1);

protected func FxReenterStart(pTarget, iEffectNumber)
{
  return(1);
}

protected func FxReenterStop(pTarget, iEffectNumber)
{
//  Log(Format("Par(0)=%i Contained()=%i", GetID(Par(0)), Contained()));
  if(GetID(pTarget) == CHEM)
    Enter(pTarget);
  if(Contained()) {
    Sound("Error");
    Message(Format("%s kann nicht aktiviert werden", GetName()), Contained());
  } else {
    RemoveObject();
  }
}