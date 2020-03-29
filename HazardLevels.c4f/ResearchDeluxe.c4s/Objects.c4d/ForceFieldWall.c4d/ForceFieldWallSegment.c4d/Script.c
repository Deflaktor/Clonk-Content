#strict

local pLast, pNext;

protected func Initialize()
{
  ScheduleCall(this(), "UpdatePhase", 1);
  return(_inherited());
}

protected func Destroy()
{
  if (pLast) ScheduleCall(pLast, "UpdatePhase" ,1);
  if (pNext) ScheduleCall(pNext, "UpdatePhase", 1);
  return(_inherited());
}

private func UpdatePhase()
{
  SetPhase(0);
  if (pLast) SetPhase(3);
  if (pNext) SetPhase(1);
  if (pLast && pNext) SetPhase(2);
  SetSolidMask(GetPhase() * GetDefCoreVal("Width", "DefCore"), 0, GetDefCoreVal("Width", "DefCore"), GetDefCoreVal("Height", "DefCore"));
}
